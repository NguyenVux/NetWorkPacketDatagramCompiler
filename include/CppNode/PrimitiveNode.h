#pragma once
#include <CppNode/NodeBase.h>


//////////////////////////////////////////////////////////////////////////////////////
class SHORT : public NodeBase{
public:
	SHORT();
	virtual std::string toString() override;
  	virtual NodeInitializeResult Initialize(const pugi::xml_node& i_node) override;
	virtual size_t getSize() override;
	virtual ~SHORT() = default;	
};


//////////////////////////////////////////////////////////////////////////////////////
class LONG : public NodeBase{
public:
	LONG();
	virtual std::string toString() override;
  	virtual NodeInitializeResult Initialize(const pugi::xml_node& i_node) override;
	virtual size_t getSize() override;
	virtual ~LONG() = default;	
};


//////////////////////////////////////////////////////////////////////////////////////
class BYTE : public NodeBase{
public:
	BYTE();
	virtual std::string toString() override;
  	virtual NodeInitializeResult Initialize(const pugi::xml_node& i_node) override;
	virtual size_t getSize() override;
	virtual ~BYTE() = default;	
};
