#include "Polynomial.hpp"

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
