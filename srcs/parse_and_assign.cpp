/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_assign.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:13:06 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/12 15:13:12 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

void	parse_and_assign( const std::vector<Token>& tokens, Context& ctx )
{
	if (tokens.empty())
		return ;

	std::string			targetVarName = "";
	std::vector<Token>	expressionToken;
	bool				isAssignment = false;

	if (tokens.size() >= 2 && tokens[1].value == "=")
	{
		if (tokens[0].type == TokenType::VARIABLE)
		{
			targetVarName = tokens[0].value;
			isAssignment = true;
			expressionToken.assign(tokens.begin() + 2, tokens.end());
		}
		else
			throw std::runtime_error("Syntax Error: Left side of '=' must be a variable.");	
	}
	else
		expressionToken = tokens;

	Parser	parser(expressionToken);
	NodePtr	ast = parser.parse();
	VarType	result = ast->eval(ctx);

	if (isAssignment)
	{
		ctx[targetVarName] = result;
		std::cout << targetVarName << " = ";
	}
	std::visit([](const auto& v)
	{
		std::cout << v << std::endl;
	}, result);
}
