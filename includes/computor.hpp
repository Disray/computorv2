/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 09:40:35 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/08 10:08:59 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <string>
#include <stdexcept>
#include <variant>
#include "types.hpp"

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

using VarType = std::variant<Real, Complex, Matrix>;

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
	VarType operator()(const Real& scl, const Matrix& m) const
	{
		if (op == "*")
			return (m * scl);
		if (op == "+")
			throw std::runtime_error("Cannot add scalar and matrix");
		if (op == "-")
			throw std::runtime_error("Cannot sub scalar and matrix");
		if (op == "/")
			throw std::runtime_error("Cannot divide scalar and matrix");
		throw std::runtime_error("Unknown operator");
	}
	VarType operator()(const Complex& a, const Real& b) const
	{
		if (op == "+")
			return (a + b);
		if (op == "-")
			return (a - b);
		if (op == "*")
			return (a * b);
		if (op == "/")
			return (a / b);
		return (Complex(0.));
	}
	template<typename T, typename U>
	VarType operator()(const T& a, const U& b)
	{	
		static_cast<void>(a);
		static_cast<void>(b);
		throw std::runtime_error("Invalid type operation");
	}
};

void	process_input( const std::vector<Token>&, std::map<std::string, VarType>& );