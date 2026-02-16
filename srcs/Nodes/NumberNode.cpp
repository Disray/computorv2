
#include "NumberNode.hpp"

NumberNode::NumberNode( Real v ) : value(v) {}

NodePtr	NumberNode::clone() const
{
	return (std::make_unique<NumberNode>(value));
}

VarType	NumberNode::eval( Context& ) const
{
	return (value);
}
