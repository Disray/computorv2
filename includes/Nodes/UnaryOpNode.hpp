#pragma once

#include "BaseNode.hpp"
#include "Visitors.hpp"

class UnaryOpNode : public BaseNode
{
	private:
		OpKind	op;
		NodePtr	child;

	public:
		UnaryOpNode( OpKind, NodePtr );

		NodePtr	clone() const override;
		VarType	eval( Context& ctx ) const override;
};
