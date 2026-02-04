/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinaryOpVisitor.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:31:57 by rrichard          #+#    #+#             */
/*   Updated: 2026/02/02 20:13:13 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Visitors/BinaryOpVisitor.hpp"

VarType	BinaryOpVisitor::operator()( const Real& a, const Real& b ) const
{
	switch (value)
	{
		case OpKind::ADD: return (a + b);
		case OpKind::SUB: return (a - b);
		case OpKind::MUL: return (a * b);
		case OpKind::DIV: return (a / b);
		case OpKind::MOD: return (a % b);
		case OpKind::POW: return (maths::pow(a, static_cast<int>(b.getReal())));
		default:
			throw std::runtime_error("Unknown operator");
	}
}

VarType BinaryOpVisitor::operator()( const Matrix<Real>& a, const Matrix<Real>& b ) const
{
	switch (value)
	{
		case OpKind::ADD: return (a + b);
		case OpKind::SUB: return (a - b);
		case OpKind::MUL: return (a * b);
		case OpKind::MUL_MAT: return (a.mul_mat(b));
		case OpKind::DIV:
			throw std::runtime_error("Matrix division not supported");
		default:
			throw std::runtime_error("Unknown operator");
	}
}

VarType BinaryOpVisitor::operator()( const Matrix<Complex>& a, const Matrix<Complex>& b ) const
{
	switch (value)
	{
		case OpKind::ADD: return (a + b);
		case OpKind::SUB: return (a - b);
		case OpKind::MUL: return (a * b);
		case OpKind::MUL_MAT: return (a.mul_mat(b));
		case OpKind::DIV:
			throw std::runtime_error("Matrix division not supported");
		default:
			throw std::runtime_error("Unknown operator");
	}
}

VarType BinaryOpVisitor::operator()( const Real& scl, const Matrix<Real>& m ) const
{
	switch (value)
	{
		case OpKind::MUL: return (m * scl);
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

VarType BinaryOpVisitor::operator()( const Real& scl, const Matrix<Complex>& m ) const
{
	switch (value)
	{
		case OpKind::MUL: return (m * scl);
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
		case OpKind::ADD: return (z + b);
		case OpKind::SUB: return (z - b);
		case OpKind::MUL: return (z * b);
		case OpKind::DIV: return (z / b);
		default:
			throw std::runtime_error("Unknown operator");
	}
}

VarType BinaryOpVisitor::operator()( const Real& a, const Complex& z ) const
{
	switch (value)
	{
		case OpKind::ADD: return (a + z);
		case OpKind::SUB: return (a - z);
		case OpKind::MUL: return (a * z);
		case OpKind::DIV: return (a / z);
		default:
			throw std::runtime_error("Unknown operator");
	}
}

VarType	BinaryOpVisitor::operator()( const Complex& z1, const Complex& z2 ) const
{
	switch (value)
	{
		case OpKind::ADD: return (z1 + z2);
		case OpKind::SUB: return (z1 - z2);
		case OpKind::MUL: return (z1 * z2);
		case OpKind::DIV: return (z1 / z2);
		default:
			throw std::runtime_error("Unknown operator");
	}
}

VarType	BinaryOpVisitor::operator()( const Polynomial& p1, const Polynomial& p2 ) const
{
	switch (value)
	{
		case OpKind::ADD: return (p1 + p2);
		case OpKind::SUB: return (p1 - p2);
		case OpKind::MUL: return (p1 * p2);
		case OpKind::DIV: return (p1 / p2);
		case OpKind::MOD: return (p1 % p2);
		default:
			throw std::runtime_error("Unkown operator");
	}
}

VarType	BinaryOpVisitor::operator()( const Real& x, const Polynomial& p ) const
{
	switch (value)
	{
		case OpKind::ADD: return (x + p);
		case OpKind::SUB: return (x - p);
		case OpKind::MUL: return (x * p);
		case OpKind::DIV: return (x / p);
		default:
			throw std::runtime_error("Unkown operator");
	}
}

VarType	BinaryOpVisitor::operator()( const Polynomial& x, const Real& p ) const
{
	switch (value)
	{
		case OpKind::ADD: return (p + x);
		case OpKind::SUB: return (p - x);
		case OpKind::MUL: return (p * x);
		case OpKind::DIV: return (p / x);
		case OpKind::POW:
		{
			if (p < 0 || Real(static_cast<int>(p)) != p)
				throw std::runtime_error("Invalid exponent");
			return (x.pow(static_cast<int>(p)));
		}
		default:
			throw std::runtime_error("Unkown operator");
	}
}

template<typename T, typename U>
VarType BinaryOpVisitor::operator()( const T& a, const U& b ) const
{	
	static_cast<void>(a); static_cast<void>(b);
	throw std::runtime_error("Invalid type operation");
}

VarType	apply_binary_op( const OpKind& op, const VarType& lhs, const VarType& rhs )
{
	return (std::visit(BinaryOpVisitor{op}, lhs, rhs));
}
