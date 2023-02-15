#include <CppNode/NodeBase.h>
#include <string>




void NodeBase::SetName(std::string i_name)
{
	m_name = i_name;
}
std::string NodeBase::GetName() const
{
	return m_name;
}

std::string NodeBase::GetKeyWord() const {
	return m_keyWord;
}
