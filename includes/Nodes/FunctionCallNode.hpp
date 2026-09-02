#pragma once

#include "BaseNode.hpp"

class FunctionCallNode : public BaseNode
{
	private:
		std::string	name;
		NodePtr		arg;

	public:
		FunctionCallNode( std::string, NodePtr );

		NodePtr	clone() const override;
		VarType	eval( Context& ) const override;
};
