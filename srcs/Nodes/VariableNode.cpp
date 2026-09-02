#include "VariableNode.hpp"

VariableNode::VariableNode( std::string n ) : name(std::move(n)) {}

NodePtr	VariableNode::clone() const
{
	return (std::make_unique<VariableNode>(name));
}

VarType	VariableNode::eval( Context& ctx ) const
{
	auto	it = ctx.find(name);
	if (it != ctx.end())
		return (it->second);

	Polynomial	sym({0, 1});
	sym.setVarName(name);
	return (sym);
}
