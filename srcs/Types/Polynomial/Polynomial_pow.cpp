#include "Polynomial.hpp"

Polynomial	Polynomial::pow( int exp ) const
{
	if (exp < 0)
		throw std::runtime_error("Negative exponent for polynomials not supported");
	Polynomial	res(Real(1));
	Polynomial	base = *this;

	while (exp > 0)
	{
		if (exp % 2 == 1)
			res = res * base;
		base = base * base;
		exp /= 2;
	}
	return (res);
}
