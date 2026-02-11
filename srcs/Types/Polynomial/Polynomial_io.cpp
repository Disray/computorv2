#include "Polynomial.hpp"

PolyPrint	Polynomial::print( const std::string& var ) const
{
	return (PolyPrint{*this, var});
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
