#include "Maths.hpp"

namespace maths
{
	Real	sqrt( const Real& x )
	{
		if (x <= 0.0)
			return (0.0);

		Real		guess = x / 2;
		const Real	tolerance = 1e-6;

		while (true)
		{
			Real	other_side = x / guess;
			Real	new_guess = (guess + other_side) / 2;

			Real	diff = abs(guess - new_guess);

			if (diff < tolerance)
				return (new_guess);
			guess = new_guess;
		}
	}

	Complex	sqrt( const Complex& z )
	{
		Real	z_abs = maths::abs(z);

		Real	real_part = maths::sqrt((z_abs + z.getReal()) / Real(2));
		Real	imag_part = z.getImag() / maths::abs(z.getImag()) * maths::sqrt((z_abs - z.getReal()) / Real(2));

		return (Complex(real_part, imag_part));
	}

	Complex	exp( const Complex& z, size_t terms )
	{
		Complex	sum(1, 0);
		Complex	current_term(1, 0);

		for (size_t i = 1; i < terms; i++)
		{
			current_term = (current_term * z) / Real(i);
			sum += current_term;
		}
		return (sum);
	}

	Real	exp( const Real& x, size_t terms )
	{
		Real	sum(1);
		Real	current_term(1);

		for (size_t i = 1; i < terms; i++)
		{
			current_term = (current_term * x) / i;
			sum += current_term;
		}
		return (sum);
	}
}
