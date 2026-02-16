
#include "ImaginaryNode.hpp"

NodePtr	ImaginaryNode::clone() const
{
	return (std::make_unique<ImaginaryNode>());
}

VarType	ImaginaryNode::eval( Context& ) const
{
	return (Complex(0, 1));
}