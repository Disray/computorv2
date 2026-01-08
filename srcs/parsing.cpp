/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 09:43:39 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/08 10:19:13 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.hpp"
#include "types.hpp"

static int	get_precedence( const std::string& op )
{
	if (op == "*" || op == "/" || op == "%")
		return (2);
	if (op == "+" || op == "-")
		return (1);
	return (0);
}

static VarType	evaluate( const std::vector<Token>& tokens, const std::map<std::string, VarType>& variables )
{
	std::stack<VarType>	_stack;

	for (const auto& token : tokens)
	{
		if (token.type == NUMBER)
			_stack.push(Real(std::stod(token.value)));
		else if (token.type == VARIABLE)
		{
			if (variables.find(token.value) == variables.end())
				throw std::runtime_error("Variable not found: " + token.value);
			_stack.push(variables.at(token.value));
		}
		else if (token.type == OPERATOR)
		{
			if (_stack.size() < 2)
				throw std::runtime_error("Not enough operands");

			VarType	rhs = _stack.top(); _stack.pop();
			VarType lhs = _stack.top(); _stack.pop();
			VarType	result = std::visit(MathVisitor{token.value}, lhs, rhs);

			_stack.push(result);
		}
	}
	if (_stack.size() != 1)
		throw std::runtime_error("Error: wrong expression.");
	return (_stack.top());
}

static std::vector<Token>	shunting_yard( const std::vector<Token>& tokens )
{
	std::vector<Token>	output_queue;
	std::stack<Token>	op_stack;

	for (const auto& token : tokens)
	{
		if (token.type == NUMBER || token.type == VARIABLE)
			output_queue.push_back(token);
		else if (token.type == OPERATOR)
		{
			if (token.value == "(")
				op_stack.push(token);
			else if (token.value == ")")
			{
				while (!op_stack.empty() && op_stack.top().value != "(")
				{
					output_queue.push_back(op_stack.top());
					op_stack.pop();
				}
				if (!op_stack.empty())
					op_stack.pop();
				else
					throw std::runtime_error("Mismatched parentheses");
			}
			else
			{
				while (!op_stack.empty() && op_stack.top().value != "(" && get_precedence(op_stack.top().value) >= get_precedence(token.value))
				{
					output_queue.push_back(op_stack.top());
					op_stack.pop();
				}
				op_stack.push(token);
			}
		}
	}
	while (!op_stack.empty())
	{
		if (op_stack.top().value == "(")
			throw std::runtime_error("Mismatched parentheses");
		output_queue.push_back(op_stack.top());
		op_stack.pop();
	}
	return (output_queue);
}

void	process_input( const std::vector<Token>& allTokens, std::map<std::string, VarType>& variables )
{
	if (allTokens.empty())
		return ;
	
	std::string			targetVarName = "";
	std::vector<Token>	expressionToken;
	bool				isAssignment = false;

	if (allTokens.size() >= 2 && allTokens[1].value == "=")
	{
		if (allTokens[0].type == VARIABLE)
		{
			targetVarName = allTokens[0].value;
			isAssignment = true;
			expressionToken.assign(allTokens.begin() + 2, allTokens.end());
		}
		else
			throw std::runtime_error("Syntax Error: Left side of '=' must be a variable.");	
	}
	else
		expressionToken = allTokens;
	std::vector<Token>	rpn = shunting_yard(expressionToken);
	VarType				result = evaluate(rpn, variables);

	if (isAssignment)
	{
		variables[targetVarName] = result;
		std::cout << targetVarName << " = ";
	}
	std::visit([](const auto& v) { std::cout << v << std::endl; }, result);
}
