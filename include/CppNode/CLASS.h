#pragma once 
#include "CppNode/NodeFactory.h"
#include <CppNode/NodeBase.h>
#include <memory>
#include <pugixml.hpp>
#include <set>


struct compareNodePtr {
	bool operator()(const std::shared_ptr<NodeBase>& l, const std::shared_ptr<NodeBase>& r) const
	{
		return l->GetName() < r->GetName();
	}
};

class CLASS : public NodeBase {
private:
	std::set<std::shared_ptr<NodeBase>, compareNodePtr> m_publicNodes;
	std::set<std::shared_ptr<NodeBase>, compareNodePtr> m_protectedNodes;
	std::set<std::shared_ptr<NodeBase>, compareNodePtr> m_privateNodes;
public:
	CLASS();
	virtual NodeInitializeResult Initialize(const pugi::xml_node& i_node) override;
	void AddPublicNode(std::shared_ptr<NodeBase> i_publicNode);
	void AddProtectedNode(std::shared_ptr<NodeBase> i_protectedNode);
	void AddPrivateNode(std::shared_ptr<NodeBase> i_privatedNode);
	virtual std::string toString() override;
	virtual ~CLASS() = default;
};