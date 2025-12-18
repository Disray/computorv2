/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:09:02 by rrichard          #+#    #+#             */
/*   Updated: 2025/12/18 13:17:53 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/includes/Complex.hpp"
#include "types/includes/Real.hpp"
#include "types/includes/Matrix.hpp"
#include <string>
#include <map>
#include <variant>
#include <regex>

enum TokenType
{
	NUMBER,
	VARIABLE,
	OPERATOR,
	UNKOWN
};

struct Token
{
	std::string	value;
	TokenType	type;
};

struct MathVisitor
{
	std::string	op;

	VarType	operator()(const Real& a, const Real& b) const
	{
		if (op == "+")
			return (a + b);
		if (op == "-")
			return (a - b);
		if (op == "*")
			return (a * b);
		if (op == "/")
			return (a / b);
		throw std::runtime_error("Unknown operator");
	}
	VarType operator()(const Matrix& a, const Matrix& b) const
	{
		if (op == "+")
			return (a + b);
		if (op == "-")
			return (a - b);
		if (op == "*")
			return (a * b);
		if (op == "/")
			throw std::runtime_error("Matrix division not supported");
		throw std::runtime_error("Unknown operator");
	}
};

using VarType = std::variant<Real, Complex, Matrix>;
std::map<std::string, VarType> variables;

static int	get_precedence( const std::string& op )
{
	if (op == "*" || op == "/" || op == "%")
		return (2);
	if (op == "+" || op == "-")
		return (1);
	return (0);
}

VarType	evaluate( const std::vector<Token>& tokens )
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

void	process_input( const std::vector<Token>& allTokens )
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
	VarType				result = evaluate_rpn(rpn, variables);

	if (isAssignment)
	{
		variables[targetVarName] = result;
		std::cout << targetVarName << " = ";
	}
}

int	main( void )
{
	std::string	input;

	getline(std::cin, input);
	try
	{
		std::regex 			pattern("([0-9]+(\\.[0-9]+)?)|([a-zA-Z][a-zA-Z0-9_]*)|([\\+\\-\\*\\/%\\(\\)=])");
		auto				words_begin = std::sregex_iterator(input.begin(), input.end(), pattern);
		auto				words_end	= std::sregex_iterator();
		std::vector<Token>	tokenList;

		for (std::sregex_iterator i = words_begin; i != words_end; i++)
		{
			std::smatch	match = *i;
			std::string	match_str = match.str();
			TokenType	type = UNKOWN;

			if (isdigit(match_str[0]))
				type = NUMBER;
			else if (isalpha(match_str[0]))
				type = VARIABLE;
			else
				type = OPERATOR;
			tokenList.push_back({match_str, type});
		}
		auto topostfix = shunting_yard(tokenList);
		for (auto& i : topostfix)
			std::cout << i.value << " ";
		std::cout << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}