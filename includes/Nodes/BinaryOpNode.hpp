#pragma once

#include "BaseNode.hpp"
#include "Visitors.hpp"

class BinaryOpNode : public BaseNode
{
	private:
		OpKind	op;
		NodePtr	left, right;

	public:
		BinaryOpNode( OpKind, NodePtr, NodePtr );
		
		NodePtr	clone() const override;
		VarType	eval( Context& ) const override;
};
