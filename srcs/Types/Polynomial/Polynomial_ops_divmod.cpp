#include "Polynomial.hpp"

Polynomial&	Polynomial::operator/=( const Real& x )
{
	if (x == Real(0.))
		throw std::runtime_error("Error: Division by zero");

	Real	inv = Real(1.) / x;

	return (*this *= inv);
}

std::pair<Polynomial, Polynomial>	Polynomial::euclidean_div( const Polynomial& b ) const
{
	if (b.getCoeffs().empty())
		throw std::runtime_error("Error: division by zero polynomial");

	Polynomial	quotient;
	Polynomial	remainder = *this;

	while (!remainder.coeffs.empty() && remainder.degree() >= b.degree())
	{
		size_t	deg_diff = remainder.degree() - b.degree();
		Real	coef_ratio = remainder.coeffs.back() / b.coeffs.back();

		Polynomial	term;
		term.coeffs.resize(deg_diff + 1, 0);
		term.coeffs.back() = coef_ratio;

		quotient = quotient + term;

		Polynomial	to_substract = b * term;
		remainder = remainder - to_substract;
	}
	return {quotient, remainder};
}

Polynomial	Polynomial::operator%( const Polynomial& b ) const
{
	return (euclidean_div(b).second);
}

Polynomial	Polynomial::operator/( const Polynomial& b ) const
{
	return (euclidean_div(b).first);
}
