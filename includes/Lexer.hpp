#pragma once

#include <map>
#include <string>
#include <vector>
#include "RuntimeTypes.hpp"

class Lexer
{
	private:
		using TokenDef = std::pair<TokenType, OpKind>;

		Token	createSymbolToken( const std::string& str ) const;

	public:
		Lexer();
		~Lexer();

		std::vector<Token>	tokenize( const std::string& input ) const;
};
