/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:26:21 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/14 15:33:39 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

NodePtr	Parser::parse_matrix()
{
	std::vector<std::vector<NodePtr>>	rows;

	do
	{
		if (!match(TokenType::BRACKET_MATRIX_OPEN))
			throw std::runtime_error("Expected '[' to start matrix row");

		std::vector<NodePtr>	row;

		row.push_back(parse_expression());
		while (match(TokenType::COMMA))
			row.push_back(parse_expression());
		if (!match(TokenType::BRACKET_MATRIX_CLOSE))
			throw std::runtime_error("Expected ']' to close matrix row");
		rows.push_back(std::move(row));
	} while (match(TokenType::SEMICOLON));
	
	if (!match(TokenType::BRACKET_MATRIX_CLOSE))
		throw std::runtime_error("Expected ']' to close matrix");
	return (std::make_unique<MatrixNode>(std::move(rows)));
}

Real	parse_real_literal( const std::string& s )
{
	size_t	idx = 0;
	double	v = 0.;

	try
	{
		v = std::stod(s, &idx);
	}
	catch(const std::exception& e)
	{
		throw std::runtime_error("Invalid number literal: " + s);
	}
	if (idx != s.size())
		throw std::runtime_error("Invalid number literal: " + s);
	return (Real(v));
	
}

NodePtr	Parser::parse_primary()
{
	if (match(TokenType::NUMBER))
		return (std::make_unique<NumberNode>(parse_real_literal(tokens[pos - 1].value)));
	if (match(TokenType::VARIABLE))
	{
		std::string	name = tokens[pos - 1].value;

		if (match(TokenType::BRACKET_OPEN))
		{
			auto	arg = parse_expression();
			consume(TokenType::BRACKET_CLOSE);
			return (std::make_unique<FunctionCallNode>(name, std::move(arg)));
		}
		return (std::make_unique<VariableNode>(name));
	}
	if (match(TokenType::IMAGINARY))
		return (std::make_unique<ImaginaryNode>());
		
	if (match(TokenType::BRACKET_OPEN))
	{
		auto	expr = parse_expression();

		if (!match(TokenType::BRACKET_CLOSE))
			throw std::runtime_error("Expected ')'");
		return (expr);
	}
	if (match(TokenType::BRACKET_MATRIX_OPEN))
		return (parse_matrix());
	throw std::runtime_error("Unexpected token");
}

NodePtr	Parser::parse_factor()
{
	if (match_op(OpKind::ADD))
		return (parse_factor());
	if (match_op(OpKind::SUB))
		return (std::make_unique<UnaryOpNode>(OpKind::SUB, parse_factor()));
	return (parse_primary());
}

NodePtr	Parser::parse_term()
{
	auto	left = parse_factor();

	while (match_op(OpKind::MULT) || match_op(OpKind::DIV))
	{
		OpKind	op = tokens[pos - 1].value == "*" ? OpKind::MULT : OpKind::DIV;
		auto	right = parse_factor();

		left = std::make_unique<BinaryOpNode>(op, std::move(left), std::move(right));
	}
	return (left);
}

NodePtr	Parser::parse_expression()
{
	auto	left = parse_term();

	while (match_op(OpKind::ADD) || match_op(OpKind::SUB))
	{
		OpKind	op = tokens[pos - 1].value == "+" ? OpKind::ADD : OpKind::SUB;
		auto	right = parse_term();

		left = std::make_unique<BinaryOpNode>(op, std::move(left), std::move(right));
	}
	return (left);
}

const Token&	Parser::peek() const
{
	return (tokens[pos]);
}

const Token&	Parser::advance()
{
	return (tokens[pos++]);
}

const Token&	Parser::consume( TokenType expected )
{
	if (pos >= tokens.size())
		throw std::runtime_error("Unexpected end of input");
	if (peek().type != expected)
		throw std::runtime_error("Unexpected token");
	return (advance());
}

bool			Parser::match( TokenType type )
{
	if (pos < tokens.size() && peek().type == type)
	{
		advance();
		return (true);
	}
	return (false);
}

bool			Parser::match_op( OpKind op )
{
	if (pos >= tokens.size())
		return (false);
	
	const Token&	t = peek();

	if (t.type != TokenType::OPERATOR)
		return (false);
	
	if ((op == OpKind::ADD  && t.value == "+") ||
		(op == OpKind::SUB  && t.value == "-" )||
		(op == OpKind::MULT && t.value == "*") ||
		(op == OpKind::DIV  && t.value == "/"))
	{
		advance();
		return (true);
	}
	return (false);
}

NodePtr	Parser::parse()
{
	std::cout << "\n\n";
	for (auto& i : tokens)
		std::cout << i.value << std::endl;
	auto	ast = parse_expression();

	if (pos < tokens.size())
		throw std::runtime_error("Unexpected token at end of expression: " + tokens[pos].value);
	return (ast);
}
