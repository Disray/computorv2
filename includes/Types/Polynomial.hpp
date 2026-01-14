/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Polynomial.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:28:00 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/14 15:06:45 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Real.hpp"
#include "Complex.hpp"
#include <vector>

class Polynomial
{
	private:
		Real	a;
		Real	b;
		Real	c;

	public:
		Polynomial();
		Polynomial( Real, Real, Real );

		int		degree() const;
		Real	eval( const Real& ) const;
		Complex	eval( const Complex& ) const;

		std::vector<Real>	solve() const;
		
		friend std::ostream&	operator<<( std::ostream&, Polynomial );
};