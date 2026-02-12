/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Polynomial.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:28:00 by rrichard          #+#    #+#             */
/*   Updated: 2026/02/12 18:38:47 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Real.hpp"
#include "Complex.hpp"
#include "Matrix.hpp"
#include <vector>
#include <string>
#include <variant>

class Polynomial;

struct PolyPrint
{
	const Polynomial&	poly;
	std::string			var;
};

std::ostream&	operator<<( std::ostream&, const PolyPrint& );
using Root = std::variant<Real, Complex>;

class Polynomial
{
	private:
		std::vector<Real>	coeffs;

		std::pair<Polynomial, Polynomial>	euclidean_div( const Polynomial& b ) const;
		std::vector<Root>					solve_degree_0( bool ) const;
		std::vector<Root>					solve_degree_1( bool ) const;
		std::vector<Root>					solve_degree_2( bool ) const;

	public:
		Polynomial() = default;
		Polynomial( std::initializer_list<Real> );
		Polynomial( Real );
		Polynomial( const Polynomial& ) = default;

		int							degree() const;

		Real						eval( const Real& ) const;
		Complex						eval( const Complex& ) const;
		Polynomial					eval( const Polynomial& ) const;
		Matrix<Real>				eval( const Matrix<Real>& ) const;
		Matrix<Complex>				eval( const Matrix<Complex>& ) const;

		template <class Variant>
		requires requires { std::variant_size_v<std::remove_cvref_t<Variant>>; }
		std::remove_cvref_t<Variant>	eval( const Variant& arg ) const
		{
			using V = std::remove_cvref_t<Variant>;
			return std::visit([this](auto&& actualArg) -> V {
				return V{ this->eval(actualArg) };
			}, arg);
		}

		std::vector<Root>			solve( bool verbose = false ) const;
		void						trim();
		bool						empty() const noexcept;
		PolyPrint					print( const std::string& varName = "x" ) const;
		const std::vector<Real>&	getCoeffs() const;
		Polynomial					pow( int ) const;
		
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
		
		Polynomial	operator/( const Polynomial& ) const;
		Polynomial&	operator/=( const Polynomial& );
		Polynomial&	operator/=( const Real& );
		
		Polynomial&	operator=( const Polynomial& ) = default;
		bool		operator==( const Polynomial& ) const noexcept;
		
		Polynomial	operator%( const Polynomial& ) const;
};

Polynomial	operator+( const Polynomial&, const Real& );
Polynomial	operator+( const Real&, const Polynomial& );
Polynomial	operator-( const Polynomial&, const Real& );
Polynomial	operator-( const Real&, const Polynomial& );
Polynomial	operator*( const Polynomial&, const Real& );
Polynomial	operator*( const Real&, const Polynomial& );
Polynomial	operator/( const Polynomial&, const Real& );
Polynomial	operator/( const Real&, const Polynomial& );
