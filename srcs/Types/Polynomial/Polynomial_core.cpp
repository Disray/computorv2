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
	while (coeffs.size() > 1 && coeffs.back() == Real(0.))
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
