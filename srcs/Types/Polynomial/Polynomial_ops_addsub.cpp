#include "Polynomial.hpp"

Polynomial	Polynomial::operator+( const Polynomial& other ) const noexcept
{
	Polynomial	result = *this;

	if (result.size() < other.size())
		result.coeffs.resize(other.size(), Real(0));

	for (size_t i = 0; i < other.size(); i++)
		result.coeffs[i] = result.coeffs[i] + other.coeffs[i];

	result.trim();
	return (result);
}

Polynomial	Polynomial::operator-( const Polynomial& other ) const noexcept
{
	Polynomial	result = *this;

	if (result.size() < other.size())
		result.coeffs.resize(other.size(), Real(0));

	for (size_t i = 0; i < other.size(); i++)
		result.coeffs[i] = result.coeffs[i] - other.coeffs[i];

	result.trim();
	return (result);
}

Polynomial	Polynomial::operator-() const
{
	Polynomial	result;

	result.coeffs.reserve(size());
	for (const Real& val : coeffs)
		result.coeffs.push_back(-val);
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
		if (size() == 1 && coeffs[0] == Real(0.))
			coeffs.pop_back();
	}
	return (*this);
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
		if (size() == 1 && coeffs[0] == Real(0.))
			coeffs.pop_back();
	}
	return (*this);
}
