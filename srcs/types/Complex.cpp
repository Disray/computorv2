/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Complex.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:39:01 by rrichard          #+#    #+#             */
/*   Updated: 2025/12/18 18:32:48 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/types.hpp"

Complex::Complex() : real(0.0), imag(0.0) {}

Complex::Complex( double r, double i ) : real(r), imag(i) {}

Complex::Complex( double r ) : real(r), imag(0.0) {}

Complex		Complex::operator+( const Complex& other ) const noexcept
{
	Complex z(0, 0);

	z.real = this->real + other.real;
	z.imag = this->imag + other.imag;
	return (z);
}

Complex		Complex::operator+( const Real& real ) const noexcept
{
	Complex	z = *this;

	z.real += real.getReal();
	return (z);
}

Complex		Complex::operator-( const Complex& other ) const noexcept
{
	Complex z(0, 0);

	z.real = this->real - other.real;
	z.imag = this->imag - other.imag;
	return (z);
}

Complex		Complex::operator-( const Real& real ) const noexcept
{
	Complex	z = *this;

	z.real -= real.getReal();
	return (z);
}

Complex		Complex::operator*( const Complex& other ) const noexcept
{
	Complex	z(0, 0);

	z.real = this->real * other.real - this->imag * other.imag;
	z.imag = this->real * other.imag + this->imag * other.real;
	return (z);
}

Complex		Complex::operator*( const Real& real ) const noexcept
{
	Complex	z = *this;
	
	z.real *= real.getReal();
	z.imag *= real.getReal();
	return (z);
}

Complex		Complex::operator/( const Complex& other ) const noexcept
{
	Complex z(0, 0);

	z.real = (this->real * other.real + this->imag * other.imag) / (other.real * other.real + other.imag * other.imag);
	z.imag = (this->imag * other.real - this->real * other.imag) / (other.real * other.real + other.imag * other.imag);
	return (z);
}

Complex		Complex::operator/( const Real& real ) const
{
	if (real.getReal() == 0.)
		throw std::runtime_error("Error: cannot divide by zero");

	Complex z = *this;

	z.real /= real.getReal();
	z.imag /= real.getReal();
	return (z);
}

Complex		Complex::operator-() const
{
	return (Complex(-real, -imag));
}

Complex&	Complex::operator+=( const Complex& other ) noexcept
{
	real += other.real;
	imag += other.imag;
	return (*this);
}

Complex&	Complex::operator-=( const Complex& other ) noexcept
{
	real -= other.real;
	imag -= other.imag;
	return (*this);
}

Complex&	Complex::operator*=( const Complex& other ) noexcept
{
	double real = this->real;
	double imag = this->imag;

	real = real * other.real - imag * other.imag;
	imag = real * other.imag + imag * other.real;
	return (*this);
}

Complex&	Complex::operator/=( const Complex& other ) noexcept
{
	double real = this->real;
	double imag = this->imag;

	real = (real * other.real + imag * other.imag) / (other.real * other.real + other.imag * other.imag);
	imag = (imag * other.real - real * other.imag) / (other.real * other.real + other.imag * other.imag);
	return (*this);
}

bool	Complex::operator==( const Complex& other ) const noexcept
{
	return (this->real == other.real && this->imag == other.imag);
}

Complex	Complex::conj() const
{
	Complex	z(0, 0);

	z.real = this->real;
	z.imag = -this->imag;
	return (z);
}

std::ostream&	operator<<( std::ostream& os, const Complex& z )
{
	constexpr double eps = 1e-9;

	auto near = [&](double x, double target)
	{
		return (std::abs(x - target) < eps);
	};

	double	re = z.real;
	double	im = z.imag;

	if (std::abs(im) < eps)
	{
		os << re;
		return (os);
	}
	if (std::abs(re) < eps)
	{
		if (near(im, 1))
			os << "i";
		else if (near(im, -1))
			os << "-i";
		else
			os << im << "i";
		return (os);
	}
	os << re << " ";
	if (near(im, 1))
		os << "+ i";
	else if (near(im, -1))
		os << " - i";
	else if (im > 0)
		os << "+ " << im << "i";
	else
		os << "- " << -im << "i";
	return (os);
}