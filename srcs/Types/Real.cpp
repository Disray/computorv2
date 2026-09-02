#include "Real.hpp"
#include "Fraction.hpp"
#include "Maths.hpp"

Real::Real() : value(0.0) {}

Real::Real( double r ) : value(r) {}

Real	Real::operator+( const Real& other ) const noexcept
{
	Real	r(0.);

	r.value = this->value + other.value;
	return (r);
}

Real	Real::operator-( const Real& other ) const noexcept
{
	Real	r(0.);

	r.value = this->value - other.value;
	return (r);
}

Real	Real::operator*( const Real& other ) const noexcept
{
	Real	r(0.);
	
	r.value = this->value * other.value;
	return (r);
}

Real	Real::operator/( const Real& other ) const
{
	if (other.value == 0.)
		throw std::runtime_error("Error: cannot divide by zero");

	Real	r(0.);

	r.value = this->value / other.value;
	return (r);
}

Real	Real::operator%( const Real& other ) const
{
	if (other == 0)
		throw std::runtime_error("Error: cannot modulo by zero");

	long	quotient = static_cast<long>(*this / other);

	return (*this - static_cast<Real>(quotient) * other);
}

Real::operator long() const
{
	return (static_cast<long>(this->value));
}

Real::operator int() const
{
	return (static_cast<int>(this->value));
}

Real::operator double() const
{
	return (this->getValue());
}

Real	Real::operator-() const noexcept
{
	return (Real(-value));
}

Real&	Real::operator+=( const Real& other ) noexcept
{
	value += other.value;
	return (*this);
}

Real&	Real::operator-=( const Real& other ) noexcept
{
	value -= other.value;
	return (*this);
}

Real&	Real::operator*=( const Real& other ) noexcept
{
	value *= other.value;
	return (*this);
}

Real&	Real::operator/=( const Real& other )
{
	if (other.value == 0.)
		throw std::runtime_error("Error: cannot divide by zero.");

	value /= other.value;
	return (*this);
}

bool	Real::operator==( const Real& other ) const noexcept
{
	return (this->value == other.value);
}

double	Real::getValue() const
{
	return (this->value);
}

std::ostream&	operator<<( std::ostream& os, const Real& r )
{
	double			val = r.getValue();
	const double	eps = 1e-10;

	if (maths::abs(val) < eps)
	{
		os << 0;
		return (os);
	}

	if (maths::abs(val - maths::round(val)) < eps)
	{
		os << static_cast<long long>(maths::round(val));
		return (os);
	}

	Fraction	piFrac(0, 1);

	if (Fraction::fromDouble(val / maths::pi, piFrac) && piFrac.getDenom() <= 12)
	{
		if (piFrac.getNum() == 1)
			os << "PI";
		else if (piFrac.getNum() == -1)
			os << "-PI";
		else
			os << piFrac.getNum() << "PI";

		if (piFrac.getDenom() != 1)
			os << "/" << piFrac.getDenom();
		return (os);
	}

	double	squared = val * val;
	if (maths::abs(squared - maths::round(squared)) < eps)
	{
		long long intSq = static_cast<long long>(maths::round(squared));

		if (intSq > 1 && intSq <= 50)
		{
			if (val < 0.0)
				os << "-";
			os << "sqrt(" << intSq << ")";
			return (os);
		}
	}

	Fraction	f(0, 1);

	if (Fraction::fromDouble(val, f) && f.getDenom() != 1 && f.getDenom() <= 100)
		os << f;
	else
		os << val;
	return (os);
}

Real	Real::square() const noexcept
{
	return (Real(value * value));
}

Real	Real::abs() const
{
	return ((value < 0) ? -value : value);
}
