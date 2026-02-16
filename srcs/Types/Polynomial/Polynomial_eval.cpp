#include "Polynomial.hpp"
#include "Maths.hpp"
#include <variant>

Real	Polynomial::eval( const Real& x ) const
{
	if (empty())
		return (Real(0.));

	Real	result = coeffs.back();

	for (size_t i = coeffs.size() - 1; i-- > 0;)
	{
		// HERE CAN USE std::fma(result, x, coeffs[i])
		result = (result * x) + coeffs[i];
	}
	return (result);
}

Complex Polynomial::eval( const Complex& z ) const
{
	if (empty())
		return (Complex(0.));

	Complex	result(coeffs.back());

	for (size_t i = coeffs.size() - 1; i-- > 0;)
		result = (result * z) + coeffs[i];
	return (result);
}

Polynomial	Polynomial::eval( const Polynomial& other ) const
{
	if (coeffs.empty()) return (Polynomial(0));
	
	Polynomial	result(coeffs.back());

	for (size_t i = coeffs.size() - 1; i-- > 0;)
		result = (result * other) + coeffs[i];
	return (result);
}

Matrix<Real>	Polynomial::eval( const Matrix<Real>& m ) const
{
	if (m.getRows() != m.getCols())
		throw std::runtime_error("Evaluation only possible on square matrices");

	Matrix<Real>	result(m.getRows(), m.getCols());
	Matrix<Real>	id = m.identity();

	for (int i = 0; i <= degree(); i++)
	{
		if (coeffs[i] != 0)
		{
			if (i == 0)
				result = result + (id * coeffs[i]);
			else
				result = result + (m.pow(i) * coeffs[i]);
		}
	}
	return (result);
}

Matrix<Complex>	Polynomial::eval( const Matrix<Complex>& m ) const
{
	if (m.getRows() != m.getCols())
		throw std::runtime_error("Evaluation only possible on square matrices");

	Matrix<Complex>	result(m.getRows(), m.getCols());
	Matrix<Complex>	id = m.identity();

	for (int i = 0; i <= degree(); i++)
	{
		if (coeffs[i] != 0)
		{
			if (i == 0)
				result = result + (id * coeffs[i]);
			else
				result = result + (m.pow(i) * coeffs[i]);
		}
	}
	return (result);
}
