/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Visitors.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 10:16:11 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/12 10:43:50 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "computor.hpp"

struct UnaryOpVisitor
{
	OpKind	value;

	VarType	operator()( const Real& )    const;
	VarType	operator()( const Complex& ) const;
	VarType	operator()( const Matrix& )  const;
};

struct BinaryOpVisitor
{
	OpKind	value;

	VarType	operator()( const Real&, const Real& ) const;
	VarType operator()( const Complex&, const Real& ) const;
	VarType	operator()( const Real&, const Complex& ) const;
	VarType	operator()( const Complex&, const Complex& ) const;

	VarType operator()( const Matrix&, const Matrix& ) const;
	VarType operator()( const Real&, const Matrix& ) const;

	template<typename T, typename U>
	VarType operator()( const T&, const U& ) const;
};

VarType	apply_unary_op( const OpKind&, const VarType& );
VarType	apply_binary_op( const OpKind&, const VarType&, const VarType& );
