#pragma once
#include <pugixml.hpp>
#include <memory>
#include <CppNode/INode.h>
#include "CppNode/NodeBase.h"
#include "utils/result.h"


enum class CreateNodeErrorCode{
	NodeRootNotFound,
	UnKnowNodeType,
	GenericError,
	NodeInitializeError
};

using NodePtr = std::shared_ptr<NodeBase>;
using CreateNodeError = VuxNguyen::error<CreateNodeErrorCode>;
using CreateNodeResult = VuxNguyen::result<NodePtr,CreateNodeError>;

class NodeFactory{
private:
public: 
	NodeFactory() = default;
	CreateNodeResult CreateTree(const pugi::xml_document& i_doc);
	static CreateNodeResult CreateNode(const pugi::xml_node& i_xmlNode);
};