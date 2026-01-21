/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_assign.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:13:06 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/21 18:08:00 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include <type_traits>

int		find_equal_index( const std::vector<Token>& tokens )
{
	for (size_t i = 0; i < tokens.size(); i++)
	{
		if (tokens[i].type == TokenType::EQUAL)
			return (static_cast<int>(i));
	}
	return (-1);
}

void	parse_and_assign( const std::vector<Token>& tokens, Context& ctx )
{
	if (tokens.empty())
		return ;

	std::string			targetName;
	std::string			paramName;
	std::vector<Token>	expressionToken;
	bool				isAssignment = false;
	bool				isFunctionAssignment = false;

	int					eq = find_equal_index(tokens);
	if (eq != -1)
	{
		if (eq == 1 && tokens[0].type == TokenType::VARIABLE)
		{
			targetName = tokens[0].value;
			isAssignment = true;
		}
		else if (eq == 4
			&& tokens[0].type == TokenType::VARIABLE
			&& tokens[1].type == TokenType::BRACKET_OPEN
			&& tokens[2].type == TokenType::VARIABLE
			&& tokens[3].type == TokenType::BRACKET_CLOSE)
		{
			targetName = tokens[0].value;
			paramName = tokens[2].value;
			isAssignment = true;
			isFunctionAssignment = true;
		}
		else
			throw std::runtime_error("Syntax Error: Left side of '=' must be a variable.");
		expressionToken.assign(tokens.begin() + eq + 1, tokens.end());
	}
	else
		expressionToken = tokens;

	Parser	parser(expressionToken);
	NodePtr	ast = parser.parse();
	Context	evalCtx = ctx;

	if (isFunctionAssignment)
		evalCtx[paramName] = Polynomial({0., 1.});

	VarType	result = ast->eval(evalCtx);

	if (isAssignment)
	{
		if (isFunctionAssignment && !std::holds_alternative<Polynomial>(result))
			throw std::runtime_error("Function definition must evaluate to a polynomial");
		ctx[targetName] = result;
		if (isFunctionAssignment)
			std::cout << targetName << "(" << paramName << ") = ";
		else
			std::cout << targetName << " = ";
	}
	std::visit([&paramName, isFunctionAssignment](const auto& v)
	{
		using T	= std::decay_t<decltype(v)>;

		if constexpr (std::is_same_v<T, Polynomial>)
		{
			std::string pVar = (isFunctionAssignment && !paramName.empty()) ? paramName : "x";

			std::cout << v.print(pVar) << std::endl;
		}
		else
		{
			std::cout << v << std::endl;
		}
	}, result);
}

