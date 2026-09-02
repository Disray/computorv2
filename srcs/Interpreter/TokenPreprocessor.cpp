#include "TokenPreprocessor.hpp"

namespace
{
	bool	endsExpression( const Token& token )
	{
		return (token.type == TokenType::NUMBER    ||
				token.type == TokenType::VARIABLE  || 
				token.type == TokenType::IMAGINARY || 
				token.type == TokenType::BRACKET_CLOSE);
	}

	bool	startsExpression( const Token& token )
	{
		return (token.type == TokenType::NUMBER    ||
				token.type == TokenType::VARIABLE  ||
				token.type == TokenType::IMAGINARY ||
				token.type == TokenType::BRACKET_OPEN);
	}

	void	prePassArity( std::vector<Token>& tokens )
	{
		bool	expects_operands = true;

		for (auto& token : tokens)
		{
			if (token.type == TokenType::VARIABLE || token.type == TokenType::NUMBER || token.type == TokenType::IMAGINARY)
				expects_operands = false;
			else if (token.type == TokenType::BRACKET_OPEN)
				expects_operands = true;
			else if (token.type == TokenType::BRACKET_CLOSE)
				expects_operands = false;
			else if (token.type == TokenType::OPERATOR)
			{
				token.arity = expects_operands ? Arity::UNARY : Arity::BINARY;
				expects_operands = true;
			}
		}
	}

	void	prePassImplMulti( std::vector<Token>& tokens )
	{
		size_t	i = 0;

		while (i + 1 < tokens.size())
		{
			if (endsExpression(tokens[i])              &&
				startsExpression(tokens[i + 1])        &&
				!(tokens[i].type == TokenType::VARIABLE &&
				tokens[i + 1].type == TokenType::BRACKET_OPEN))
			{
				tokens.insert(tokens.begin() + (i + 1), Token("*", TokenType::OPERATOR, Arity::BINARY, OpKind::MUL));
				i++;
			}
			else
				i++;
		}
	}
}

namespace token_preproc
{
	void	normalize( std::vector<Token>& tokens )
	{
		prePassArity(tokens);
		prePassImplMulti(tokens);
	}
}
