#pragma once 
#include <CppNode/INode.h>
#include <pugixml.hpp>
#include <string>


class NodeBase : public INode {
protected:
	NodeBase(std::string i_keyWord) : m_keyWord(i_keyWord){}
	std::string m_keyWord;
	std::string m_name;
	
public:
	bool operator<(const NodeBase &other) const
	{
		return m_name.compare(other.GetName());
	}
	void SetName(std::string i_name);
	std::string GetKeyWord() const;
	virtual size_t getSize() = 0;
	
	virtual std::string getSource(){
		return std::string();
	}
	std::string GetName() const;
	virtual ~NodeBase() = default;

};
