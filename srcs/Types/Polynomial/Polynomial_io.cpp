
#include "Polynomial.hpp"

std::ostream&	operator<<( std::ostream& os, const Polynomial& p )
{
	if (p.empty())
		return (os << "0");

	bool	printed_any = false;

	for (size_t i = p.size(); i-- > 0;)
	{
		Real	coeff = p.coeffs[i];

		if (coeff == 0)
			continue;

		if (printed_any)
			os << (coeff >= 0 ? " + " : " - ");
		else if (coeff < 0)
			os << "-";

		Real	mag = maths::abs(coeff);
		bool	is_one = (mag == 1);

		if (i == 0 || !is_one)
			os << mag;
		if (i > 0)
		{
			os << p.varName;
			if (i > 1)
				os << "^" << i;
		}
		printed_any = true;
	}
	if (!printed_any)
		return (os << "0");
	return (os);
}
