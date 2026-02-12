#pragma once

#include "computor.hpp"
#include <map>
#include <string>
#include <vector>

class Lexer
{
	private:
		using TokenDef = std::pair<TokenType, OpKind>;

		void	prePassArity( std::vector<Token>& tokens ) const;
		void	prePassImplMulti( std::vector<Token>& tokens ) const;

		bool	endsExpression( const Token& token ) const;
		bool	startsExpression( const Token& token ) const;

		Token	createSymbolToken( const std::string& str ) const;

	public:
		Lexer();
		~Lexer();

		std::vector<Token>	tokenize( const std::string& input ) const;
};
