#pragma once
#include <string>
#include <pugixml.hpp>
#include <utils/result.h>



enum class NodeInitializeErrorCode{
	GenericError,
	MissingName
};

using NodeInitializeError = VuxNguyen::error<NodeInitializeErrorCode>;
using NodeInitializeResult = VuxNguyen::result<void,NodeInitializeError>;


class INode{
public:
	virtual std::string toString() = 0;
	virtual NodeInitializeResult Initialize(const pugi::xml_node& i_node) = 0;
};