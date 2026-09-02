#pragma once

#include "BaseNode.hpp"

class VariableNode : public BaseNode
{
	private:
		std::string	name;
	
	public:
		explicit VariableNode( std::string );

		NodePtr	clone() const override;
		VarType	eval( Context& ) const override;
};
