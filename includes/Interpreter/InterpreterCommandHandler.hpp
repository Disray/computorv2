#pragma once

#include "RuntimeTypes.hpp"
#include <string>
#include <vector>

namespace interpreter_cmd
{
	bool	handle( const std::vector<Token>& tokens, Context& ctx, const std::vector<std::string>& history );
}
