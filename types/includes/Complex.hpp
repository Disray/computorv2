/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Complex.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:27:58 by rrichard          #+#    #+#             */
/*   Updated: 2025/12/16 15:55:48 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

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
		Complex		operator+( const Complex& ) const noexcept;
		Complex		operator-( const Complex& ) const noexcept;
		Complex		operator*( const Complex& ) const noexcept;
		Complex		operator/( const Complex& ) const noexcept;
		Complex		operator-() const;
		Complex&	operator=( const Complex& ) = default;
		Complex&	operator+=( const Complex& ) noexcept;
		Complex&	operator-=( const Complex& ) noexcept;
		Complex&	operator*=( const Complex& ) noexcept;
		Complex&	operator/=( const Complex& ) noexcept;
		bool		operator==( const Complex& ) const noexcept;

		friend std::ostream&	operator<<( std::ostream&, const Complex& );
};
