#include "Maths.hpp"

namespace
{
	double	arctan_impl( double x, size_t terms )
	{
		double	x_abs = static_cast<double>(maths::abs(x));
		double	num;
		double	step;

		if (x_abs <= 1)
		{
			num = x_abs;
			step = x_abs * x_abs;
		}
		else
		{
			num = 1.0 / x_abs;
			step = 1.0 / (x_abs * x_abs);
		}
		
		double	sum = 0.0;
		int		denom = 1;
		int		sign = 1;

		for (size_t k = 0; k < terms; k++)
		{
			sum += sign * (num / denom); 
			num *= step;
			denom += 2;
			sign = -sign;
		}
		
		if (x_abs > 1)
			sum = maths::pi / 2.0 - sum;
		if (x < 0)
			sum = -sum;

		return (sum);
	}

	double	arctan2_impl( double a, double b, size_t terms = 50 )
	{
		if (b == 0)
		{
			if (a >= 0) return (0.0);
			else  return (maths::pi);
		}

		if (a == 0)
		{
			if (b > 0) return (maths::pi / 2);
			else return (-maths::pi / 2);
		}
		double	ratio = static_cast<double>(maths::abs(b / a));
		double	alpha = arctan_impl(ratio, terms);
		double	theta = 0.0;

		if (a > 0 && b > 0)		 theta = alpha;
		else if (a < 0 && b > 0) theta = maths::pi - alpha;
		else if (a < 0 && b < 0) theta = maths::pi + alpha;
		else if (a > 0 && b < 0) theta = -alpha;

		return (theta);
	}
}

namespace maths
{
	Complex cos( const Complex& z, size_t terms )
	{
		Complex iz(-z.getImag(), z.getReal());
		Complex	numerator = maths::exp(iz, terms) + maths::exp(-iz, terms);

		return (numerator / Real(2));
	}

	Real	cos( const Real& r, size_t terms )
	{
		Real	x = r;

		while (x < 0)
			x += 2 * pi;
		while (x > 2 * pi)
			x -= 2 * pi;
		
		Real	result = 1.0;
		Real	term = 1.0;

		for (size_t k = 1; k < terms; k++)
		{
			term *= -x * x / ((2 * k) * (2 * k - 1));
			result += term;
		}
		return (result);
	}

	Complex sin( const Complex& z, size_t terms )
	{
		Complex iz(-z.getImag(), z.getReal());
		Complex	numerator = maths::exp(iz, terms) - maths::exp(-iz, terms);

		return (numerator / Complex(0, 2));
	}

	Real	sin( const Real& r, size_t terms )
	{
		Real	x = r;

		while (x < -pi)
			x += 2 * pi;
		while (x > pi)
			x -= 2 * pi;

		Real	result = x;
		Real	term = x;

		for (size_t k = 1; k < terms; k++)
		{
			term *= -x * x / ((2 * k) * (2 * k + 1));
			result += term;
		}
		return (result);
	}

	Real	tan( const Real& x, size_t terms )
	{
		return (Real(maths::sin(x, terms) / maths::cos(x, terms)));
	}

	Complex	tan( const Complex& z, size_t terms )
	{
		return (sin(z, terms) / cos(z, terms));
	}

	Real arctan( const Real& x, size_t terms )
	{
		return (Real(arctan_impl(x.getValue(), terms)));
	}

	Real	arctan2( const Real& a, const Real& b )
	{
		return (Real(arctan2_impl(a.getValue(), b.getValue())));
	}
}
