#include "Polynomial.hpp"

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
