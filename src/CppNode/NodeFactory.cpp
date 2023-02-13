#include "CppNode/INode.h"
#include "utils/result.h"
#include <CppNode/NodeFactory.h>
#include <CppNode/CLASS.h>
#include <CppNode/PrimitiveNode.h>

#include <cstring>
#include <memory>
#include <sstream>
#include <iostream>


CreateNodeResult NodeFactory::CreateTree(const pugi::xml_document& i_doc)
{
	auto docIt = i_doc.children();
	if(docIt.empty())
	{
		return CreateNodeError(CreateNodeErrorCode::NodeRootNotFound,"document empty");
	}
	pugi::xml_node_iterator rootXmlNode = docIt.begin();

	return CreateNode(*rootXmlNode);
}

CreateNodeResult NodeFactory::CreateNode(const pugi::xml_node& i_xmlNode){

	NodePtr node;
	if(strcmp(i_xmlNode.name(),"class") == 0)
	{
		node = std::make_shared<CLASS>();
	}
	else if(strcmp(i_xmlNode.name(),"byte") == 0)
	{
		node = std::make_shared<BYTE>();
	}
	else if(strcmp(i_xmlNode.name(),"short") == 0)
	{
		node = std::make_shared<SHORT>();
	}
	else if(strcmp(i_xmlNode.name(),"long") == 0)
	{
		node = std::make_shared<LONG>();
	}
	if(node != nullptr)
	{
		NodeInitializeResult result =  node->Initialize(i_xmlNode);
		if(result != VuxNguyen::success)
		{
			return CreateNodeError(CreateNodeErrorCode::UnKnowNodeType,result.error().what()); 
		}
		return node;
	}
	return CreateNodeError(CreateNodeErrorCode::UnKnowNodeType,"UnKnow Node Type"); 
}

