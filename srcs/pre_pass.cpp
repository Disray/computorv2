/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_pass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 10:33:18 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/09 14:28:51 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.hpp"

void	pre_pass_arity( std::vector<Token>& tokens )
{
	bool	expects_operands = true;

	for (auto& token : tokens)
	{
		if (token.type == VARIABLE || token.type == NUMBER || token.type == IMAGINARY)
		{
			expects_operands = false;
			continue;
		}
		if (token.type == OPERATOR)
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
			token.arity = expects_operands ? UNARY : BINARY;
			expects_operands = true;
		}
	}
}

static bool	ends_expression( const Token& token )
{
	if (token.type == NUMBER || token.type == VARIABLE || token.type == IMAGINARY || token.value == ")")
		return (true);
	return (false);
}

static bool	starts_expression( const Token& token )
{
	if (token.type == NUMBER || token.type == VARIABLE || token.type == IMAGINARY || token.value == "(" || token.arity == UNARY)
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
			tokens.insert(tokens.begin() + (i + 1), {"*", OPERATOR, BINARY});
			i++;
		}
		else
			i++;
	}
}