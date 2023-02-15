#pragma once 
#include "CppNode/NodeFactory.h"
#include <CppNode/NodeBase.h>
#include <memory>
#include <pugixml.hpp>
#include <unordered_set>



enum class InsertMemberErrorCode {
	NameExist,
	NullNode
};

using InsertMemberError = VuxNguyen::error<InsertMemberErrorCode>;
using InsertMemberResult = VuxNguyen::result<void, InsertMemberError>;


class CLASS : public NodeBase {
private:


	struct container {
		std::unordered_set<std::string> m_set;
		std::list<std::shared_ptr<NodeBase>> m_list;
	};

	container m_publicNodes;
	container m_protectedNodes;
	container m_privateNodes;
public:
	CLASS();
	virtual NodeInitializeResult Initialize(const pugi::xml_node& i_node) override;
	InsertMemberResult InsertTo(std::shared_ptr<NodeBase> i_publicNode, container& i_list);
	virtual size_t getSize() override;
	virtual std::string toString() override;
	virtual std::string getSource() override;
	virtual ~CLASS() = default;
};
