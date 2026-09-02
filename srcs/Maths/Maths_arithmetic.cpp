#include "Maths.hpp"

namespace maths
{
	Real	min( const Real& a, const Real& b )
	{
		return ((b < a) ? b : a);
	}

	Real	max( const Real& a, const Real& b )
	{
		return ((a < b) ? b : a);
	}

	Real	abs( const Real& x )
	{
		return ((x < 0) ? -x : x);
	}

	double	abs( double x )
	{
		return ((x < 0.0) ? -x : x);
	}

	Real	scalar_norm2( const Real& x )
	{
		return (x * x);
	}

	Real	scalar_norm2( const Complex& z )
	{
		return (z.getReal() * z.getReal() + z.getImag() * z.getImag());
	}

	Real	abs( const Complex& z )
	{
		Real	a = z.getReal();
		Real	b = z.getImag();

		return (sqrt(pow(a, 2) + pow(b, 2)));
	}

	Real	pow( const Real& base, int exp )
	{
		if (exp < 0)
			return (Real(1) / pow(base, -exp));

		Real	res = 1.0;
		Real	x = base;

		while (exp > 0)
		{
			if (exp % 2 == 1)
				res *= x;
			x *= x;
			exp /= 2;
		}
		return (res);
	}

	Complex	pow( const Complex& base, int exp )
	{
		Real	m = abs(base);
		Real	a = base.getReal();
		Real	b = base.getImag();
		Real	theta = maths::arctan2(a, b);
		Complex	result(0);

		result.setReal(maths::cos(Real(exp) * theta));
		result.setImag(maths::sin(Real(exp) * theta));
		result *= maths::pow(m, exp);
		return (result);
	}

	bool	finite( double x )
	{
		return (x - x == 0.0); 
	}

	int		round( double x )
	{
		return ((int)(x >= 0.0 ? x + 0.5 : x - 0.5));
	}

	int		gcd( int a, int b )
	{
		if (b == 0)
			return (a);
		return (gcd(b, a % b));
	}

	double	floor( double num )
	{
		if (num < 0.0)	
			return ((int)num - 1);
		else
			return ((int)num);
	}

	template <typename T>
	typename std::enable_if<std::is_floating_point<T>::value, double>::type
	ceil(T x)
	{
		if (x == floor(x))
			return ((double)static_cast<long long>(x));
		return (floor(x) + 1.0);
	}
}
