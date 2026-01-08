/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 09:43:39 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/08 16:26:09 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.hpp"
#include "types.hpp"

static int	get_precedence( const Token& tok )
{
	if (tok.value == "(" || tok.value == ")")
		return (0);
	if (tok.arity == UNARY && (tok.value == "+" || tok.value == "-"))
		return (3);
	if (tok.value == "*" || tok.value == "/" || tok.value == "%")
		return (2);
	if (tok.value == "+" || tok.value == "-")
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
			if (token.arity == UNARY)
			{
				if (_stack.empty())
					throw std::runtime_error("Error: missing operand for unary operator");

				VarType value = _stack.top(); _stack.pop();
				VarType result = apply_unary_op(token.value, value);

				_stack.push(result);
				continue;
			}
			if (_stack.size() < 2)
				throw std::runtime_error("Error: missing operand for binary operator");
			
			VarType	rhs = _stack.top(); _stack.pop();
			VarType lhs = _stack.top(); _stack.pop();
			VarType	result = apply_binary_op(token.value, lhs, rhs);

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
				while (!op_stack.empty() && op_stack.top().value != "(")
				{
					const int precedence_top = get_precedence(op_stack.top());
					const int precedence_current = get_precedence(token);
					
					if ((token.arity != UNARY && precedence_top >= precedence_current)
						|| (token.arity == UNARY && precedence_top > precedence_current))
					{
						output_queue.push_back(op_stack.top());
						op_stack.pop();
					}
					else
						break;
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
	std::visit([](const auto& v)
	{
		std::cout << v << std::endl;
	}, result);
}

void	pre_pass_arity( std::vector<Token>& tokens )
{
	bool	expects_operands = true;

	for (auto& token : tokens)
	{
		if (token.type == VARIABLE || token.type == NUMBER)
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
