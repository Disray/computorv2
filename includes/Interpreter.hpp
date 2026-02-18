#pragma once

#include "Parser.hpp"
#include <vector>
#include <string>

struct Target
{
	std::string	name;
	std::string	param;
	bool		isFunction;

	Target( const std::string& n, const std::string& p, bool f ) : name(n), param(p), isFunction(f) {}
};

class Interpreter
{
	private:
		Context&	_ctx;

		int		findEqualIndex( const std::vector<Token>& tokens) const;
		Target	parseLHS( const std::vector<Token>& tokens ) const;
		void	executeQuery( const Target& target, const std::vector<Token>& rhsTokens ) const;
		void	executeAssignment( const Target& target, const std::vector<Token>& rhsTokens);

	public:
		Interpreter( Context& ctx );
		~Interpreter();

		void	processLine( std::vector<Token>& tokens );
};
