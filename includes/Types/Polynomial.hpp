/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Polynomial.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:28:00 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/21 18:11:12 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Real.hpp"
#include "Complex.hpp"
#include <vector>
#include <string>

class Polynomial;

struct PolyPrint
{
	const Polynomial&	poly;
	std::string			var;
};

std::ostream&	operator<<( std::ostream&, const PolyPrint& );

class Polynomial
{
	private:
		std::vector<Real>	coeffs;

	public:
		Polynomial() = default;
		Polynomial( std::initializer_list<Real> );
		Polynomial( Real );
		Polynomial( const Polynomial& ) = default;

		int							degree() const;
		Real						eval( const Real& ) const;
		Complex						eval( const Complex& ) const;
		std::vector<Real>			solve() const;
		void						trim();
		constexpr bool				empty() const noexcept;
		PolyPrint					print( const std::string& varName = "x" ) const;
		const std::vector<Real>&	getCoeffs() const;
		
		friend std::ostream&	operator<<( std::ostream&, const Polynomial& );

		Polynomial	operator+( const Polynomial& ) const noexcept;
		Polynomial&	operator+=( const Polynomial& ) noexcept;
		Polynomial&	operator+=( const Real& ) noexcept;

		Polynomial	operator-( const Polynomial& ) const noexcept;
		Polynomial	operator-() const;
		Polynomial&	operator-=( const Polynomial& ) noexcept;
		Polynomial&	operator-=( const Real& ) noexcept;
	
		Polynomial	operator*( const Polynomial& ) const noexcept;
		Polynomial&	operator*=( const Polynomial& ) noexcept;
		Polynomial&	operator*=( const Real& ) noexcept;
		
		Polynomial	operator/( const Polynomial& ) const noexcept;
		Polynomial&	operator/=( const Polynomial& ) noexcept;
		Polynomial&	operator/=( const Real& );
		
		Polynomial&	operator=( const Polynomial& ) = default;
		bool		operator==( const Polynomial& ) const noexcept;
};

Polynomial	operator+( const Polynomial&, const Real& );
Polynomial	operator+( const Real&, const Polynomial& );
Polynomial	operator-( const Polynomial&, const Real& );
Polynomial	operator-( const Real&, const Polynomial& );
Polynomial	operator*( const Polynomial&, const Real& );
Polynomial	operator*( const Real&, const Polynomial& );
Polynomial	operator/( const Polynomial&, const Real& );
Polynomial	operator/( const Real&, const Polynomial& );
