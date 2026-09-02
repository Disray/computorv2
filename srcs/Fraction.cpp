#include "Fraction.hpp"
#include "Maths.hpp"

Fraction::Fraction( int num, int den ) : numerator(num), denominator(den)
{
	if (denominator == 0)
		throw std::invalid_argument("Denominator cannot be zero");
	simplify();
}

void	Fraction::simplify()
{
	int	g = maths::gcd(maths::abs(numerator), maths::abs(denominator));

	numerator /= g;
	denominator /= g;
	if (denominator < 0)
	{
		numerator = -numerator;
		denominator = -denominator;
	}
}

int	Fraction::getDenom() const
{
	return (this->denominator);
}

int	Fraction::getNum() const
{
	return (this->numerator);
}

void	Fraction::print() const
{
	std::cout << numerator << "/" << denominator << std::endl;
}

std::ostream&	operator<<( std::ostream& os, const Fraction& f )
{
	os << f.numerator << "/" << f.denominator;
	return (os);
}

bool	Fraction::fromDouble( double value, Fraction& out )
{
	const double	tolerance = 1e-6;
	double			num = value;

	int				h1 = 1, h2 = 0;
	int				k1 = 0, k2 = 1;

	for (int i = 0; i < 64; i++)
	{
		int	a = static_cast<int>(maths::floor(num));

		int	h = a * h1 + h2;
		int	k = a * k1 + k2;

		h2 = h1; h1 = h;
		k2 = k1; k1 = k;

		if (k != 0)
		{
			double approx = static_cast<double>(h) / k;
			if (maths::abs(value - approx) < tolerance)
			{
				out = Fraction(h, k);
				return (true);
			}
		}
		double frac_part = num - a;
		if (frac_part < 1e-9)
			break ;
		num = 1.0 / frac_part;
	}
	return (false);
}
