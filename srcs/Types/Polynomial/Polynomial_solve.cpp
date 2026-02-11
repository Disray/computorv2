#include "Polynomial.hpp"

std::vector<Root>	Polynomial::solve( bool verbose ) const
{
	int	d = this->degree();

	if (verbose)
		std::cout << "Polynomial degree: " << d << std::endl;

	switch (d)
	{
		case 0: return (this->solve_degree_0(verbose));
		case 1: return (this->solve_degree_1(verbose));
		case 2: return (this->solve_degree_2(verbose));
		default:
			throw std::runtime_error("The polynomial degree is stricly greater than 2, I can't solve");
	}
}

std::vector<Root>	Polynomial::solve_degree_0( bool verbose ) const
{
	if (coeffs.empty() || coeffs[0] == 0)
	{
		if (verbose)
			std::cout << "All real numbers are solution\n";
		return {};
	}
	else
	{
		if (verbose)
			std::cout << "No solution\n";
		return {};
	}
}

std::vector<Root>	Polynomial::solve_degree_1( bool verbose ) const
{
	Real	a = coeffs[1];
	Real	b = (coeffs.size() > 0) ? coeffs[0] : Real(0);

	Real	res = -b / a;

	if (verbose)
	{
		std::cout << "The solution is:\n" << res << std::endl; 
	}
	return (std::vector<Root>{ Root{ res } });
}

std::vector<Root>	Polynomial::solve_degree_2( bool verbose ) const
{
	Real	a = coeffs[2];
	Real	b = (coeffs.size() > 1) ? coeffs[1] : Real(0);
	Real	c = (coeffs.size() > 0) ? coeffs[0] : Real(0);

	Real	delta = b.square() - (Real(4) * a * c);

	if (verbose)
		std::cout << "Discriminant is " << delta << std::endl;
	if (delta > 0)
	{
		Real	sqrt_delta = maths::sqrt(delta);

		Real	x1 = (-b - sqrt_delta) / (Real(2) * a);
		Real	x2 = (-b + sqrt_delta) / (Real(2) * a);

		if (verbose)
		{
			std::cout << "Strictly positive, the two solutions are:\n";
			std::cout << x1 << std::endl;
			std::cout << x2 << std::endl;
		}
		return (std::vector<Root>{ Root{ x1 }, Root{ x2 } });
	}
	else if (delta == 0)
	{
		Real	x = -b / (Real(2) * a);

		if (verbose)
			std::cout << "Discriminant is null, the solution is:\n" << x << std::endl;
		return (std::vector<Root>{Root{ x }});
	}
	else // delta < 0
	{
		Complex	i = Complex(0, 1);
		Real	sqrt_delta = maths::sqrt(-delta);

		Complex	x1 = (-b - i * sqrt_delta) / (Real(2) * a);
		Complex	x2 = (-b + i * sqrt_delta) / (Real(2) * a);

		if (verbose)
		{
			std::cout << "Strictly negative, the two solutions are:\n";
			std::cout << x1 << std::endl;
			std::cout << x2 << std::endl;
		}
		return (std::vector<Root>{ Root{ x1 }, Root{ x2 } });
	}
}