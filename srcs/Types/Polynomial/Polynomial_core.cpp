#include "Polynomial.hpp"

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
	const double	eps = 1e-14;

	while (!coeffs.empty() && maths::abs(coeffs.back().getValue()) < eps)
	{
		coeffs.pop_back();
	}
}

bool	Polynomial::empty() const noexcept
{
	return (coeffs.empty());
}

const std::vector<Real>&	Polynomial::getCoeffs() const
{
	return (coeffs);
}

size_t	Polynomial::size() const noexcept
{
	return (coeffs.size());
}

std::string	Polynomial::getVarName() const
{
	return (varName);
}

void	Polynomial::setVarName( const std::string& name )
{
	varName = name;
}
