/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Polynomial.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:32:50 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/26 20:09:20 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Polynomial.hpp"
#include "Maths.hpp"

Polynomial::Polynomial( std::initializer_list<Real> init ) : coeffs(init)
{
	trim();
}

Polynomial::Polynomial( Real scalar )
{
	coeffs.push_back(scalar);
	trim();
}

int	Polynomial::degree() const
{
	return (empty() ? 0 : coeffs.size() - 1);
}

void	Polynomial::trim()
{
	while (coeffs.size() > 1 && coeffs.back() == Real(0.))
	{
		coeffs.pop_back();
	}
}

constexpr bool	Polynomial::empty() const noexcept
{
	return (coeffs.empty());
}

Real	Polynomial::eval( const Real& x ) const
{
	if (empty())
		return (Real(0.));

	Real	result = coeffs.back();

	for (size_t i = coeffs.size() - 1; i-- > 0;)
	{
		// HERE CAN USE std::fma(result, x, coeffs[i])
		result = (result * x) + coeffs[i];
	}
	return (result);
}

Complex Polynomial::eval( const Complex& z ) const
{
	if (empty())
		return (Complex(0.));

	Complex	result(coeffs.back().getReal()); // NEED CONSTRUCTOR FOR Complex(Real)

	for (size_t i = coeffs.size() - 1; i-- > 0;)
		result = (result * z) + coeffs[i];
	return (result);
}

PolyPrint	Polynomial::print( const std::string& var ) const
{
	return (PolyPrint{*this, var});
}

const std::vector<Real>&	Polynomial::getCoeffs() const
{
	return (coeffs);
}

std::ostream&	operator<<( std::ostream& os, const PolyPrint& p )
{
	const auto&	coeffs = p.poly.getCoeffs();

	if (coeffs.empty())
		return (os << "0");

	bool	printed_any = false;

	for (size_t i = coeffs.size(); i-- > 0;)
	{
		Real coeff = coeffs[i];

		if (coeff == Real(0.))
			continue;

		double real = coeff.getReal();

		if (printed_any)
			os << (real >= 0. ? " + " : " - ");
		else if (real < 0.)
			os << " - ";

		Real	mag = (real < 0.) ? -coeff : coeff;

		bool	is_one = (mag == Real(1.));

		if (i == 0 || !is_one)
			os << mag;
		if (i > 0)
		{
			os << p.var;
			if (i > 1)
				os << "^" << i;
		}
		printed_any = true;
	}
	if (!printed_any)
		return (os << "0");
	return (os);
}

Polynomial	Polynomial::operator+( const Polynomial& other ) const noexcept
{
	Polynomial	result;
	size_t		max_deg = maths::max(coeffs.size(), other.coeffs.size());

	result.coeffs.resize(max_deg, 0);
	for (size_t i = 0; i < max_deg; i++)
	{
		Real	val1 = (i < coeffs.size()) ? coeffs[i] : 0;
		Real	val2 = (i < other.coeffs.size()) ? other.coeffs[i] : 0;
		result.coeffs[i] = val1 + val2;
	}
	result.trim();
	return (result);
}

Polynomial	Polynomial::operator-( const Polynomial& other ) const noexcept
{
	Polynomial	result;
	size_t		max_deg = maths::max(coeffs.size(), other.coeffs.size());

	result.coeffs.resize(max_deg, 0);
	for (size_t i = 0; i < max_deg; i++)
	{
		Real	val1 = (i < coeffs.size()) ? coeffs[i] : 0;
		Real	val2 = (i < other.coeffs.size()) ? other.coeffs[i] : 0;
		result.coeffs[i] = val1 - val2;
	}
	result.trim();
	return (result);
}

Polynomial	Polynomial::operator-() const
{
	Polynomial	result;

	result.coeffs.reserve(coeffs.size());
	for (const Real& val : coeffs)
		result.coeffs.push_back(-val);
	return (result);
}

Polynomial	Polynomial::operator*( const Polynomial& other ) const noexcept
{
	if (coeffs.empty() || other.coeffs.empty())
		return (Polynomial(Real(0.)));

	size_t		new_size = coeffs.size() + other.coeffs.size() - 1;
	Polynomial	result;

	result.coeffs.assign(new_size, 0);
	for (size_t i = 0; i < coeffs.size(); i++)
	{
		for (size_t j = 0; j < other.coeffs.size(); j++)
		{
			result.coeffs[i + j] += coeffs[i] * other.coeffs[j];
		}
	}
	result.trim();
	return (result);
}

Polynomial&	Polynomial::operator+=( const Real& x ) noexcept
{
	if (empty())
	{
		if (x != Real(0.))
			coeffs.push_back(x);
	}
	else
	{
		coeffs[0] += x;
		if (coeffs.size() == 1 && coeffs[0] == Real(0.))
			coeffs.pop_back();
	}
	return (*this);
}

Polynomial	operator+( const Polynomial& p, const Real& x )
{
	Polynomial result = p;

	result += x;
	return (result);
}

Polynomial	operator+( const Real& x, const Polynomial& p )
{
	return (p + x);
}

Polynomial&	Polynomial::operator-=( const Real& x ) noexcept
{
	if (empty())
	{
		if (x != Real(0.))
			coeffs.push_back(-x);
	}
	else
	{
		coeffs[0] -= x;
		if (coeffs.size() == 1 && coeffs[0] == Real(0.))
			coeffs.pop_back();
	}
	return (*this);
}

Polynomial	operator-( const Polynomial& p, const Real& x )
{
	Polynomial result = p;

	result -= x;
	return (result);
}

Polynomial	operator-( const Real& x, const Polynomial& p )
{
	return (p - x);
}

Polynomial&	Polynomial::operator*=( const Real& x ) noexcept
{
	if (x == Real(0.))
	{
		coeffs.clear();
		return (*this);
	}
	for (size_t i = 0; i < coeffs.size(); i++)
		coeffs[i] *= x;
	return (*this);
}

Polynomial	operator*( const Polynomial& p, const Real& x )
{
	Polynomial	result = p;

	result *= x;
	return (result);
}

Polynomial	operator*( const Real& x, const Polynomial& p )
{
	return (p * x);
}

Polynomial&	Polynomial::operator/=( const Real& x )
{
	if (x == Real(0.))
		throw std::runtime_error("Error: Division by zero");

	Real	inv = Real(1.) / x;

	return (*this *= inv);
}

Polynomial	operator/( const Polynomial& p, const Real& x )
{
	Polynomial	result = p;

	result /= x;
	return (result);
}

Polynomial	operator/( const Real& x, const Polynomial& p )
{
	return (p / x);
}

// Polynomial	Polynomial::operator/( const Polynomial& p ) const
// {
	
// }

// Polynomial&	Polynomial::operator/=( const Polynomial& p )
// {
	
// }

// bool		Polynomial::operator==( const Polynomial& ) const
// {
	
// }