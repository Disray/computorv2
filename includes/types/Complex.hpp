/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Complex.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:27:58 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/09 11:47:46 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Real;

class Complex
{
	private:
		double	real;
		double	imag;
	
	public:
		Complex();
		Complex( double, double );
		Complex( double );
		Complex( const Complex& ) = default;
		~Complex() = default;
		
		Complex		conj() const;
		double		getReal() const;
		void		setReal( double );
		double		getImag() const;
		void		setImag( double );
		
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