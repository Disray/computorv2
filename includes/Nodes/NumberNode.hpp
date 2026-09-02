#pragma once

#include "BaseNode.hpp"
#include "Types/Real.hpp"

class NumberNode : public BaseNode
{
	private:
		Real	value;

	public:
		explicit NumberNode( Real );

		NodePtr	clone() const override;
		VarType	eval( Context& ) const override;
};
