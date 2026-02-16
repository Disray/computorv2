
#include "VariableNode.hpp"

VariableNode::VariableNode( std::string n ) : name(std::move(n)) {}

NodePtr	VariableNode::clone() const
{
	return (std::make_unique<VariableNode>(name));
}

VarType	VariableNode::eval( Context& ctx ) const
{
	if (!ctx.contains(name))
		throw std::runtime_error("Undefined variable: " + name);

	return (ctx.at(name));
}
