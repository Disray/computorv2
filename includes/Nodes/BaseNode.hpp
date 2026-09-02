#pragma once

#include <memory>
#include "RuntimeTypes.hpp"

class BaseNode;
using NodePtr = std::unique_ptr<BaseNode>;

class BaseNode
{
	public:
		virtual ~BaseNode() = default;

		virtual	NodePtr	clone() const = 0;
		virtual VarType	eval( Context& ) const = 0;
};
