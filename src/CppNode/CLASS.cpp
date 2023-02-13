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
		if(strcmp(childNode.attribute("visibility").value(),"public") == 0){

			AddPublicNode(result.extract_payload());
		}
		else if (strcmp(childNode.attribute("visibility").value(),"protected") == 0)
		{
			AddProtectedNode(result.extract_payload());
		}
		else
		{
			AddPrivateNode(result.extract_payload());
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


void CLASS::AddPrivateNode(std::shared_ptr<NodeBase> i_privateNode)
{
	if (i_privateNode == nullptr)
	{
		return;
	}
	m_publicNodes.insert(i_privateNode);
}

void CLASS::AddPublicNode(std::shared_ptr<NodeBase> i_publicNode)
{
	if (i_publicNode == nullptr)
	{
		return;
	}
	m_publicNodes.insert(i_publicNode);
}

void CLASS::AddProtectedNode(std::shared_ptr<NodeBase> i_protectedNode)
{
	if (i_protectedNode == nullptr)
	{
		return;
	}
	m_publicNodes.insert(i_protectedNode);
}

std::string CLASS::toString()
{
	std::stringstream ss;
	ss << m_keyWord << " " << m_name << "{" << std::endl;

	//generate protected:
	if(!m_protectedNodes.empty())
	{
		ss << "protected:" << std::endl;
	}
	for (auto i : m_protectedNodes)
	{
		ss << "\t" << i->toString();
	}

	//generate Public:
	if (!m_publicNodes.empty())
	{
		ss << "public:" << std::endl;
	}
	for(auto i : m_publicNodes)
	{
		ss << "\t" << i->toString();
	}

	//generate private:
	if (!m_privateNodes.empty())
	{
		ss << "private:" << std::endl;
	}
	for (auto i : m_privateNodes)
	{
		ss << "\t" << i->toString();
	}
	ss << "};" << std::endl;

	return ss.str();
}