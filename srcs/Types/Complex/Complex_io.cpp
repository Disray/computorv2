#include "Complex.hpp"

std::ostream&	operator<<( std::ostream& os, const Complex& z )
{
	double	eps = 1e-9;

	auto near = [&](Real x, Real target)
	{
		return (Real(x - target).abs() < eps);
	};

	Real	re = z.real;
	Real	im = z.imag;

	if (im.abs() < eps)
	{
		os << re;
		return (os);
	}
	if (re.abs() < eps)
	{
		if (near(im, 1))
			os << "i";
		else if (near(im, -1))
			os << "-i";
		else
			os << im << "i";
		return (os);
	}
	os << re << " ";
	if (near(im, 1))
		os << "+ i";
	else if (near(im, -1))
		os << " - i";
	else if (im > 0)
		os << "+ " << im << "i";
	else
		os << "- " << -im << "i";
	return (os);
}
