/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Visitors.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 10:16:11 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/09 10:25:15 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "computor.hpp"

struct UnaryOpVisitor
{
	std::string	op;

	VarType	operator()( const Real& ) const;
	VarType	operator()( const Complex& ) const;
	VarType	operator()( const Matrix& ) const;
};

struct BinaryOpVisitor
{
	std::string	op;

	VarType	operator()( const Real&, const Real& ) const;
	VarType operator()( const Matrix&, const Matrix& ) const;
	VarType operator()( const Real&, const Matrix& ) const;
	VarType operator()( const Complex&, const Real& ) const;

	template<typename T, typename U>
	VarType operator()( const T&, const U& ) const;
};