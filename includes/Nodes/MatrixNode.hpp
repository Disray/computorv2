#pragma once

#include "BaseNode.hpp"

class MatrixNode : public BaseNode
{
	private:
		std::vector<std::vector<NodePtr>>	elements;
	
	public:
		explicit MatrixNode( std::vector<std::vector<NodePtr>> );
		
		NodePtr	clone() const override;
		VarType eval( Context& ctx ) const override;
};
