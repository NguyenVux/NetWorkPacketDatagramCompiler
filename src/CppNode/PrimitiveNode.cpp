#include "CppNode/INode.h"
#include "CppNode/NodeBase.h"
#include <CppNode/PrimitiveNode.h>
#include <sstream>
#include <string>
#include <pugixml.hpp>


SHORT::SHORT() : NodeBase("short") {}

std::string SHORT::toString() {
	std::stringstream ss;
	ss << m_keyWord << " " << m_name << ";" << std::endl;
	return ss.str();
}

NodeInitializeResult SHORT::Initialize(const pugi::xml_node& i_node) {
	bool isNameMissing = !i_node.attribute("name");
	if (isNameMissing)
	{
		return NodeInitializeError(NodeInitializeErrorCode::MissingName);
	}
	SetName(i_node.attribute("name").as_string());
	return NodeInitializeResult();
}

size_t SHORT::getSize(){
	return sizeof(short);
}

LONG::LONG() : NodeBase("long") {}

std::string LONG::toString() {
	std::stringstream ss;
	ss << m_keyWord << " " << m_name << ";" << std::endl;
	return ss.str();
}

NodeInitializeResult LONG::Initialize(const pugi::xml_node& i_node) {
	bool isNameMissing = !i_node.attribute("name");
	if(isNameMissing)
	{
		return NodeInitializeError(NodeInitializeErrorCode::MissingName);
	}
	SetName(i_node.attribute("name").as_string());
	return NodeInitializeResult();
}

size_t LONG::getSize(){
	return sizeof(long);
}


BYTE::BYTE() : NodeBase("char") {}

std::string BYTE::toString() {
	std::stringstream ss;
	ss << m_keyWord << " " << m_name << ";" << std::endl;
	return ss.str();
}

NodeInitializeResult BYTE::Initialize(const pugi::xml_node& i_node) {
	bool isNameMissing = !i_node.attribute("name");
	if (isNameMissing)
	{
		return NodeInitializeError(NodeInitializeErrorCode::MissingName);
	}
	SetName(i_node.attribute("name").as_string());
	return NodeInitializeResult();
}

size_t BYTE::getSize(){
	return sizeof(char);
}








