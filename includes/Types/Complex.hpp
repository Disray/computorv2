/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Complex.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:27:58 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/27 17:42:29 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "Maths.hpp"
#include "Types/Real.hpp"

class Complex
{
	private:
		Real	real;
		Real	imag;
	
	public:
		Complex();
		Complex( Real, Real );
		Complex( Real );
		Complex( const Complex& ) = default;
		~Complex() = default;
		
		Complex		conj() const;
		Real		getReal() const;
		void		setReal( Real );
		Real		getImag() const;
		void		setImag( Real );
		
		Complex		operator+( const Complex& ) const noexcept;
		Complex&	operator+=( const Complex& ) noexcept;

		Complex		operator-( const Complex& ) const noexcept;
		Complex		operator-() const;
		Complex&	operator-=( const Complex& ) noexcept;
	
		Complex		operator*( const Complex& ) const noexcept;
		Complex&	operator*=( const Complex& ) noexcept;
		
		Complex		operator/( const Complex& ) const noexcept;
		Complex&	operator/=( const Complex& ) noexcept;

		Complex&	operator=( const Complex& ) = default;
		bool		operator==( const Complex& ) const noexcept;

		friend std::ostream&	operator<<( std::ostream&, const Complex& );
};

Complex	operator+( const Complex&, const Real& );
Complex	operator+( const Real&, const Complex& );
Complex	operator-( const Complex&, const Real& );
Complex	operator-( const Real&, const Complex& );
Complex	operator*( const Complex&, const Real& );
Complex	operator*( const Real&, const Complex& );
Complex	operator/( const Complex&, const Real& );
Complex	operator/( const Real&, const Complex& );