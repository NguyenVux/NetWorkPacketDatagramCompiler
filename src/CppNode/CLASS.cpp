#include "CppNode/INode.h"
#include "CppNode/NodeBase.h"
#include "CppNode/PrimitiveNode.h"
#include "utils/result.h"
#include <CppNode/CLASS.h>
#include <CppNode/NodeFactory.h>
#include <cstddef>
#include <memory>
#include <sstream>
#include <iostream>
#include <string.h>
#include <format>

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

	ss << "#pragma once" << std::endl;
	ss << "#include <memory>" << std::endl;
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
	for(auto i : m_privateNodes.m_list)
	{
		ss << "\t" << std::format("{} get_{}() const;",i->GetKeyWord(),i->GetName()) << std::endl;
		ss << "\t" << std::format("void set_{}(const {}& i_input);",i->GetName(),i->GetKeyWord()) << std::endl;
	}

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

std::string CLASS::getSource() {
	std::stringstream ss;
	ss << std::format("#include \"{}.hpp\"",m_name) << std::endl;
	ss << "#include <WinSock2.h>" << std::endl;

	ss << std::format("std::unique_ptr<char[]> {}::Serialize() {{", m_name) << std::endl;

	size_t size = getSize();
	ss << std::format("\tstd::unique_ptr<char[]> buffer = std::make_unique<char[]>({});",size) << std::endl;
	ss << "\tsize_t index = 0;" << std::endl;
	for(auto i : m_privateNodes.m_list)
	{
		ss << "\t{" << std::endl;
		if(std::dynamic_pointer_cast<SHORT>(i) != nullptr)
		{
			std::shared_ptr<SHORT> temp = std::dynamic_pointer_cast<SHORT>(i);
			ss << std::format("\t\t{} temp = htons({});", temp->GetKeyWord(), temp->GetName()) << std::endl;
		}
		else if(std::dynamic_pointer_cast<LONG>(i) != nullptr)
		{
			std::shared_ptr<LONG> temp = std::dynamic_pointer_cast<LONG>(i);
			ss << std::format("\t\t{} temp = htonl({});", temp->GetKeyWord(), temp->GetName()) << std::endl;
		}
		else{
			ss << std::format("\t\t{} temp = {};", i->GetKeyWord(), i->GetName()) << std::endl;
		}
		ss << std::format("\t\tmemcpy(buffer.get() + index,&temp,{});",i->getSize()) << std::endl;
		ss << std::format("\t\tindex+={};",i->getSize()) << std::endl;
		ss << "\t}" << std::endl;
	}
	ss << "\treturn std::move(buffer);" << std::endl;
	ss << "}" << std::endl;
	for(auto i : m_privateNodes.m_list)
	{
		ss << std::format("{} {}::get_{}() const {{",i->GetKeyWord(),m_name,i->GetName()) << std::endl;
		ss << std::format("\treturn {};",i->GetName()) << std::endl;
		ss << "}" << std::endl;
		ss << std::endl << std::endl;
		ss << std::format("void {}::set_{}(const {}& i_input) {{",m_name,i->GetName(),i->GetKeyWord()) << std::endl;
		ss << std::format("\tthis->{} = i_input;",i->GetName()) << std::endl;
		ss << "}" << std::endl;
	}


	return ss.str();
}


