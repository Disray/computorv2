/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Complex.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:39:01 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/27 19:08:19 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Types/Complex.hpp"

Complex::Complex() : real(Real()), imag(Real()) {}

Complex::Complex( Real r, Real i ) : real(r), imag(i) {}

Complex::Complex( Real r ) : real(r), imag(0.) {}

Real	Complex::getReal() const
{
	return (this->real);
}

Real	Complex::getImag() const
{
	return (this->imag);
}

void	Complex::setReal( Real value )
{
	this->real = value;
}

void	Complex::setImag( Real value )
{
	this->imag = value;
}

Complex		Complex::operator+( const Complex& other ) const noexcept
{
	Complex z(0, 0);

	z.real = this->real + other.real;
	z.imag = this->imag + other.imag;
	return (z);
}

Complex		Complex::operator-( const Complex& other ) const noexcept
{
	Complex z(0, 0);

	z.real = this->real - other.real;
	z.imag = this->imag - other.imag;
	return (z);
}

Complex		Complex::operator*( const Complex& other ) const noexcept
{
	Complex	z(0, 0);

	z.real = this->real * other.real - this->imag * other.imag;
	z.imag = this->real * other.imag + this->imag * other.real;
	return (z);
}

Complex		Complex::operator/( const Complex& other ) const noexcept
{
	Complex z(0, 0);

	z.real = (this->real * other.real + this->imag * other.imag) / (other.real * other.real + other.imag * other.imag);
	z.imag = (this->imag * other.real - this->real * other.imag) / (other.real * other.real + other.imag * other.imag);
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
	Real	new_real = this->real;
	Real	new_imag = this->imag;

	new_real = real * other.real - imag * other.imag;
	new_imag = real * other.imag + imag * other.real;
	this->real = new_real;
	this->imag = new_imag;
	return (*this);
}

Complex&	Complex::operator/=( const Complex& other ) noexcept
{
	Real	new_real = this->real;
	Real	new_imag = this->imag;

	new_real = (real * other.real + imag * other.imag) / (other.real * other.real + other.imag * other.imag);
	new_imag = (imag * other.real - real * other.imag) / (other.real * other.real + other.imag * other.imag);
	this->real = new_real;
	this->imag = new_imag;
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
	double	eps = 1e-9;

	auto near = [&](Real x, Real target)
	{
		return (maths::abs(x - target) < eps);
	};

	Real	re = z.real;
	Real	im = z.imag;

	if (maths::abs(im) < eps)
	{
		os << re;
		return (os);
	}
	if (maths::abs(re) < eps)
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

Complex	operator+( const Complex& z, const Real& x )
{
	Complex	z1(0);

	z1.setReal(z.getReal() + x.getReal());
	z1.setImag(z.getImag());
	return (z1);
}

Complex	operator+( const Real& x, const Complex& z )
{
	Complex	z1(0);

	z1.setReal(z.getReal() + x.getReal());
	z1.setImag(z.getImag());
	return (z1);
}

Complex	operator-( const Complex& z, const Real& x )
{
	Complex	z1(0);

	z1.setReal(z.getReal() - x.getReal());
	z1.setImag(z.getImag());
	return (z1);
}

Complex	operator-( const Real& x, const Complex& z )
{
	Complex	z1(0);

	z1.setReal(x - z.getReal());
	z1.setImag(-z.getImag());
	return (z1);
}

Complex	operator*( const Complex& z, const Real& x )
{
	Complex	z1(0);

	z1.setReal(x * z.getReal());
	z1.setImag(x * z.getImag());
	return (z1);
}

Complex	operator*( const Real& x, const Complex& z )
{
	Complex	z1(0);

	z1.setReal(x * z.getReal());
	z1.setImag(x * z.getImag());
	return (z1);
}

Complex	operator/( const Complex& z, const Real& x )
{
	if (x.getReal() == 0.)
		throw std::runtime_error("Error: cannot divide by zero");

	Complex z1(0);

	z1.setReal(z.getReal() / x.getReal());
	z1.setImag(z.getImag() / x.getReal());
	return (z1);
}

Complex	operator/( const Real& x, const Complex& z )
{
	if (z.getReal() == 0. && z.getImag() == 0.)
		throw std::runtime_error("Error: cannot divide by zero");

	Complex z1(0);

	z1.setReal(x / z.getReal());
	z1.setImag(x / z.getImag());
	return (z1);
}