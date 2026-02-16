
#include "UnaryOpNode.hpp"

UnaryOpNode::UnaryOpNode( OpKind v, NodePtr c ) : op(v), child(std::move(c)) {}

NodePtr	UnaryOpNode::clone() const
{
	return (std::make_unique<UnaryOpNode>(op, child->clone()));
}

VarType	UnaryOpNode::eval( Context& ctx ) const
{
	VarType	value = child->eval(ctx);

	return (apply_unary_op(op, value));
}
