/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Visitors.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:04:32 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/09 11:29:00 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.hpp"
#include "visitors.hpp"

VarType	UnaryOpVisitor::operator()( const Real& a ) const
{
	if (op == "+")
		return (a);
	if (op == "-")
		return (Real(-a));
	throw std::runtime_error("Unknown unary operator");
}

VarType	UnaryOpVisitor::operator()( const Complex& c ) const
{
	if (op == "+")
		return (c);
	if (op == "-")
		return (Complex(-c));
	throw std::runtime_error("Unknown unary operator");
}

VarType	UnaryOpVisitor::operator()( const Matrix& m ) const
{
	if (op == "+")
		return (m);
	if (op == "-")
		return (m * Real(-1));
	throw std::runtime_error("Unknown unary operator");
}

VarType	BinaryOpVisitor::operator()( const Real& a, const Real& b ) const
{
	if (op == "+")
		return (a + b);
	if (op == "-")
		return (a - b);
	if (op == "*")
		return (a * b);
	if (op == "/")
		return (a / b);
	throw std::runtime_error("Unknown operator: " + op);
}

VarType BinaryOpVisitor::operator()( const Matrix& a, const Matrix& b ) const
{
	if (op == "+")
		return (a + b);
	if (op == "-")
		return (a - b);
	if (op == "*")
		return (a * b);
	if (op == "/")
		throw std::runtime_error("Matrix division not supported");
	throw std::runtime_error("Unknown operator: " + op);
}

VarType BinaryOpVisitor::operator()( const Real& scl, const Matrix& m ) const
{
	if (op == "*")
		return (m * scl);
	if (op == "+")
		throw std::runtime_error("Cannot add scalar and matrix");
	if (op == "-")
		throw std::runtime_error("Cannot sub scalar and matrix");
	if (op == "/")
		throw std::runtime_error("Cannot divide scalar and matrix");
	throw std::runtime_error("Unknown operator: " + op);
}

VarType BinaryOpVisitor::operator()( const Complex& z, const Real& b ) const
{
	if (op == "+")
		return (z + b);
	if (op == "-")
		return (z - b);
	if (op == "*")
		return (z * b);
	if (op == "/")
		return (z / b);
	throw std::runtime_error("Unkown operator: " + op);
}

VarType BinaryOpVisitor::operator()( const Real& a, const Complex& z ) const
{
	if (op == "+")
		return (a + z);
	if (op == "-")
		return (a - z);
	if (op == "*")
		return (a * z);
	if (op == "/")
		return (a / z);
	throw std::runtime_error("Unkown operator: " + op);
}

VarType	BinaryOpVisitor::operator()( const Complex& z1, const Complex& z2 ) const
{
	if (op == "+") return (z1 + z2);
	if (op == "-") return (z1 - z2);
	if (op == "*") return (z1 * z2);
	if (op == "/") return (z1 / z2);
	throw std::runtime_error("Unkown operator: " + op);
}

template<typename T, typename U>
VarType BinaryOpVisitor::operator()( const T& a, const U& b ) const
{	
	static_cast<void>(a); static_cast<void>(b);
	throw std::runtime_error("Invalid type operation");
}


VarType	apply_unary_op( const std::string& op, const VarType& a )
{
	return (std::visit(UnaryOpVisitor{op}, a));
}

VarType	apply_binary_op( const std::string& op, const VarType& lhs, const VarType& rhs )
{
	return (std::visit(BinaryOpVisitor{op}, lhs, rhs));
}
