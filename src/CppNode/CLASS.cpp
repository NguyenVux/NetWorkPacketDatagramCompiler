#include "CppNode/INode.h"
#include "CppNode/NodeBase.h"
#include "utils/result.h"
#include <CppNode/CLASS.h>
#include <CppNode/NodeFactory.h>
#include <sstream>
#include <iostream>
#include <string.h>

CLASS::CLASS():
	NodeBase("class")
{

}

size_t CLASS::getSize(){
	size_t size = 0;
	for(auto node : m_privateNodes.m_list)
	{
		size+= node->getSize();
	}
	for(auto node : m_publicNodes.m_list)
	{
		size+= node->getSize();
	}
	for(auto node : m_protectedNodes.m_list)
	{
		size+= node->getSize();
	}
	return size;
}

NodeInitializeResult CLASS::Initialize(const pugi::xml_node& i_node)
{
	for(auto childNode : i_node.children())
	{
		CreateNodeResult result =  NodeFactory::CreateNode(childNode);
		if(result != VuxNguyen::success)
		{
			if(result.error().errorCode() == CreateNodeErrorCode::NodeInitializeError)
			{
				return NodeInitializeError(NodeInitializeErrorCode::GenericError,"");
			}
			continue;
		}
		auto node = result.extract_payload();
		InsertMemberResult nResult;
		if(strcmp(childNode.attribute("visibility").value(),"public") == 0){

			nResult = InsertTo(node,m_publicNodes);

		}
		else if (strcmp(childNode.attribute("visibility").value(),"protected") == 0)
		{
			nResult = InsertTo(node,m_protectedNodes);
		}
		else
		{
			nResult = InsertTo(node,m_privateNodes);
		}
		if (nResult != VuxNguyen::success &&
			nResult.error().errorCode() != InsertMemberErrorCode::NullNode)
		{
			return NodeInitializeError(NodeInitializeErrorCode::GenericError, "redefined member: " + node->GetName());
		}
		
	}
	bool isNameMissing = !i_node.attribute("name");
	if (isNameMissing)
	{
		return NodeInitializeError(NodeInitializeErrorCode::MissingName);
	}
	SetName(i_node.attribute("name").as_string());
	return NodeInitializeResult();
}

InsertMemberResult CLASS::InsertTo(std::shared_ptr<NodeBase> i_node, container& i_list)
{
	if (i_node == nullptr)
	{
		return InsertMemberError(InsertMemberErrorCode::NullNode);;
	}
	if (i_list.m_set.find(i_node->GetName()) != i_list.m_set.end())
	{
		return InsertMemberError(InsertMemberErrorCode::NameExist);
	}
	i_list.m_set.insert(i_node->GetName());
	i_list.m_list.push_back(i_node);
	return InsertMemberResult();
}

std::string CLASS::toString()
{
	std::stringstream ss;
	ss << m_keyWord << " " << m_name << "{" << std::endl;

	//generate protected:
	if(!m_protectedNodes.m_set.empty())
	{
		ss << "protected:" << std::endl;
	}
	for (auto i : m_protectedNodes.m_list)
	{
		ss << "\t" << i->toString();
	}

	//generate Public:
	ss << "public:" << std::endl;
	for(auto i : m_publicNodes.m_list)
	{
		ss << "\t" << i->toString();
	}
	ss << "\t" << "std::unique_ptr<char[]> Serialize();" << std::endl;

	//generate private:
	if (!m_privateNodes.m_set.empty())
	{
		ss << "private:" << std::endl;
	}
	for (auto i : m_privateNodes.m_list)
	{
		ss << "\t" << i->toString();
	}
	ss << "};" << std::endl;

	return ss.str();
}
