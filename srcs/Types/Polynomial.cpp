/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Polynomial.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:32:50 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/14 15:12:33 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Polynomial.hpp"

Polynomial::Polynomial() : a(0.), b(0.), c(0.) {}

Polynomial::Polynomial( Real na, Real nb, Real nc ) : a(na), b(nb), c(nc) {}

int	Polynomial::degree() const
{
	if (a != Real(0.))
		return (2);
	if (b != Real(0.))
		return (1);
	return (0);
}

Real	Polynomial::eval( const Real& x ) const
{
	return (a * x * x + b * x + c);
}

Complex Polynomial::eval( const Complex& z ) const
{
	return (a * z * z + b * z + c);
}

std::ostream&	operator<<( std::ostream& os, Polynomial poly )
{
	return (os << poly.a << "x^2" << (poly.b.getReal() > 0. ? " + " : " - ") << std::abs(poly.b.getReal()) << "x" << (poly.c.getReal() > 0. ? " + " : " - ") << std::abs(poly.c.getReal()));
}

