#include "Polynomial.hpp"

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
			result.coeffs[i + j] += coeffs[i] * other.coeffs[j];
	}
	result.trim();
	return (result);
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
