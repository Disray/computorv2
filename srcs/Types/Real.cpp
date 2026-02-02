/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Real.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:03:10 by rrichard          #+#    #+#             */
/*   Updated: 2026/02/02 16:38:42 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.hpp"

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

Real	Real::operator%( const Real& other ) const
{
	if (other == 0)
		throw std::runtime_error("Error: cannot modulo by zero");

	long	quotient = static_cast<long>(*this / other);

	return (*this - static_cast<Real>(quotient) * other);
}

Real::operator long() const
{
	return (static_cast<long>(this->real));
}

Real::operator int() const
{
	return (static_cast<int>(this->real));
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

double	Real::getReal() const
{
	return (this->real);
}

std::ostream&	operator<<( std::ostream& os, const Real& r )
{
	os << r.real;
	return (os);
}

bool	Real::operator>( const Real& other ) const noexcept
{
	return (this->real > other.real);
}

bool	Real::operator<( const Real& other ) const noexcept
{
	return (this->real < other.real);
}

bool	Real::operator>=( const Real& other ) const noexcept
{
	return (this->real >= other.real);
}

bool	Real::operator<=( const Real& other ) const noexcept
{
	return (this->real <= other.real);
}

bool	Real::operator!=( const Real& other ) const noexcept
{
	return (this->real != other.real);
}