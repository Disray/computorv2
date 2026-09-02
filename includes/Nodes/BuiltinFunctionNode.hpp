#pragma once

#include "BaseNode.hpp"

class BuiltinFunctionNode : public BaseNode
{
	private:
		std::string	name;
		NodePtr		arg;

	public:
		BuiltinFunctionNode( std::string, NodePtr );

		NodePtr	clone() const override;
		VarType	eval( Context& ) const override;
};
