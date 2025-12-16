/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Real.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:03:10 by rrichard          #+#    #+#             */
/*   Updated: 2025/12/16 16:36:53 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Real.hpp"

Real::Real() : real(0.0) {}

Real::Real( double r ) : real(r) {}

Real	Real::operator+( const Real& other ) const noexcept
{
	Real	r(0.);

	r.real = this->real + other.real;
	return (r);
}

Real	Real::operator-( const Real& other ) const noexcept
{
	Real	r(0.);

	r.real = this->real - other.real;
	return (r);
}

Real	Real::operator*( const Real& other ) const noexcept
{
	Real	r(0.);
	
	r.real = this->real * other.real;
	return (r);
}

Real	Real::operator/( const Real& other ) const
{
	if (other.real == 0.)
		throw std::runtime_error("Error: cannot divide by zero");

	Real	r(0.);

	r.real = this->real / other.real;
	return (r);
}

Real	Real::operator-() const noexcept
{
	return (Real(-real));
}

Real&	Real::operator+=( const Real& other ) noexcept
{
	real += other.real;
	return (*this);
}

Real&	Real::operator-=( const Real& other ) noexcept
{
	real -= other.real;
	return (*this);
}

Real&	Real::operator*=( const Real& other ) noexcept
{
	real *= other.real;
	return (*this);
}

Real&	Real::operator/=( const Real& other )
{
	if (other.real == 0.)
		throw std::runtime_error("Error: cannot divide by zero.");

	real /= other.real;
	return (*this);
}

bool	Real::operator==( const Real& other ) const noexcept
{
	return (this->real == other.real);
}