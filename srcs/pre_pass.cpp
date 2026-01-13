/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_pass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 10:33:18 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/13 12:19:56 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.hpp"

void	pre_pass_arity( std::vector<Token>& tokens )
{
	bool	expects_operands = true;

	for (auto& token : tokens)
	{
		if (token.type == TokenType::VARIABLE || token.type == TokenType::NUMBER || token.type == TokenType::IMAGINARY)
		{
			expects_operands = false;
			continue;
		}
		if (token.type == TokenType::OPERATOR)
		{
			if (token.value == "(")
			{
				expects_operands = true;
				continue;
			}
			if (token.value == ")")
			{
				expects_operands = false;
				continue;
			}
			token.arity = expects_operands ? Arity::UNARY : Arity::BINARY;
			expects_operands = true;
		}
	}
}

bool	ends_expression( const Token& token )
{
	if (token.type == TokenType::NUMBER    ||
		token.type == TokenType::VARIABLE  || 
		token.type == TokenType::IMAGINARY || 
		token.type == TokenType::BRACKET_CLOSE)
		return (true);
	return (false);
}

bool	starts_expression( const Token& token )
{
	if (token.type == TokenType::NUMBER    ||
		token.type == TokenType::VARIABLE  ||
		token.type == TokenType::IMAGINARY ||
		token.type == TokenType::BRACKET_OPEN)
		return (true);
	return (false);
}

void	pre_pass_impl_multi( std::vector<Token>& tokens )
{
	size_t	i = 0;

	while (i + 1 < tokens.size())
	{
		if (ends_expression(tokens[i]) && starts_expression(tokens[i + 1]))
		{
			tokens.insert(tokens.begin() + (i + 1), Token("*", TokenType::OPERATOR, Arity::BINARY));
			i++;
		}
		else
			i++;
	}
}