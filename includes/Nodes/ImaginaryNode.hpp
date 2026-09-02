#pragma once

#include "BaseNode.hpp"

class ImaginaryNode : public BaseNode
{
	NodePtr	clone() const override;
	VarType	eval( Context& ) const override;
};
