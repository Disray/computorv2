/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Visitors.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:04:32 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/12 11:41:39 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Visitors.hpp"

VarType	UnaryOpVisitor::operator()( const Real& a ) const
{
	switch (value)
	{
		case OpKind::ADD: return (a);
		case OpKind::SUB: return (-a);
		default:
			throw std::runtime_error("Unknown unary operator");
	}
}

VarType	UnaryOpVisitor::operator()( const Complex& c ) const
{
	switch (value)
	{
		case OpKind::ADD: return (c);
		case OpKind::SUB: return (-c);
		default:
			throw std::runtime_error("Unknown unary operator");
	}
}

VarType	UnaryOpVisitor::operator()( const Matrix& m ) const
{
	switch (value)
	{
		case OpKind::ADD: return (m);
		case OpKind::SUB: return (-m);
		default:
			throw std::runtime_error("Unknown unary operator");	
	}
}

VarType	BinaryOpVisitor::operator()( const Real& a, const Real& b ) const
{
	switch (value)
	{
		case OpKind::ADD:  return (a + b);
		case OpKind::SUB:  return (a - b);
		case OpKind::MULT: return (a * b);
		case OpKind::DIV:  return (a / b);
		default:
			throw std::runtime_error("Unknown operator");
	}
}

VarType BinaryOpVisitor::operator()( const Matrix& a, const Matrix& b ) const
{
	switch (value)
	{
		case OpKind::ADD:  return (a + b);
		case OpKind::SUB:  return (a - b);
		case OpKind::MULT: return (a * b);
		case OpKind::DIV:
			throw std::runtime_error("Matrix division not supported");
		default:
			throw std::runtime_error("Unknown operator");
	}
}

VarType BinaryOpVisitor::operator()( const Real& scl, const Matrix& m ) const
{
	switch (value)
	{
		case OpKind::MULT: return (m * scl);
		case OpKind::ADD:
			throw std::runtime_error("Cannot add scalar and matrix");
		case OpKind::SUB:
			throw std::runtime_error("Cannot sub scalar and matrix");
		case OpKind::DIV:
			throw std::runtime_error("Cannot divide scalar and matrix");
		default:
			throw std::runtime_error("Unknown operator");
	}
}

VarType BinaryOpVisitor::operator()( const Complex& z, const Real& b ) const
{
	switch (value)
	{
		case OpKind::ADD:  return (z + b);
		case OpKind::SUB:  return (z - b);
		case OpKind::MULT: return (z * b);
		case OpKind::DIV:  return (z / b);
		default:
			throw std::runtime_error("Unknown operator");
	}
}

VarType BinaryOpVisitor::operator()( const Real& a, const Complex& z ) const
{
	switch (value)
	{
		case OpKind::ADD:  return (a + z);
		case OpKind::SUB:  return (a - z);
		case OpKind::MULT: return (a * z);
		case OpKind::DIV:  return (a / z);
		default:
			throw std::runtime_error("Unknown operator");
	}
}

VarType	BinaryOpVisitor::operator()( const Complex& z1, const Complex& z2 ) const
{
	switch (value)
	{
		case OpKind::ADD:  return (z1 + z2);
		case OpKind::SUB:  return (z1 - z2);
		case OpKind::MULT: return (z1 * z2);
		case OpKind::DIV:  return (z1 / z2);
		default:
			throw std::runtime_error("Unknown operator");
	}
}

template<typename T, typename U>
VarType BinaryOpVisitor::operator()( const T& a, const U& b ) const
{	
	static_cast<void>(a); static_cast<void>(b);
	throw std::runtime_error("Invalid type operation");
}

VarType	apply_unary_op( const OpKind& op, const VarType& a )
{
	return (std::visit(UnaryOpVisitor{op}, a));
}

VarType	apply_binary_op( const OpKind& op, const VarType& lhs, const VarType& rhs )
{
	return (std::visit(BinaryOpVisitor{op}, lhs, rhs));
}
