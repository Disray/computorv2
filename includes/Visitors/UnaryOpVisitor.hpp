/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UnaryOpVisitor.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:28:48 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/13 11:29:01 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "RuntimeTypes.hpp"

struct UnaryOpVisitor
{
	OpKind	value;

	VarType	operator()( const Real& )    const;
	VarType	operator()( const Complex& ) const;
	VarType	operator()( const Matrix<Real>& )  const;
	VarType	operator()( const Matrix<Complex>& )  const;
};
