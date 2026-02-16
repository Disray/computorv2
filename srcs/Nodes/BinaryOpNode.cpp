
#include "BinaryOpNode.hpp"

BinaryOpNode::BinaryOpNode( OpKind v, NodePtr l, NodePtr r ) : op(v), left(std::move(l)), right(std::move(r)) {}

NodePtr	BinaryOpNode::clone() const
{
	return (std::make_unique<BinaryOpNode>(op, left->clone(), right->clone()));
}

VarType	BinaryOpNode::eval( Context& ctx ) const
{
	VarType	lhs = left->eval(ctx);
	VarType	rhs = right->eval(ctx);

	return (apply_binary_op(op, lhs, rhs));
}
