#pragma once

#include "RuntimeTypes.hpp"
#include <string>
#include <vector>

namespace interpreter_eval
{
	void	execute( Context& ctx, std::vector<std::string>& history, const std::vector<Token>& tokens, bool isQuery, const std::string& rawLine );
}
