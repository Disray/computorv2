#pragma once

#include "Real.hpp"

namespace maths
{

template<typename T>
const T&	min( const T& a, const T& b ) noexcept
{
	return (b < a) ? b : a;
}

template<typename T>
const T&	max( const T& a, const T& b) noexcept
{
	return (a < b) ? b : a;
}

template<typename T>
T			abs( T x ) noexcept
{
	return (x < static_cast<T>(0) ? -x : x);
}

template<typename T>
T			pow( T base, int exp )
{
	if (exp < 0)
		return (T(1) / pow(base, -exp));

	T	res = 1.0;

	while (exp > 0)
	{
		if (exp % 2 == 1)
			res *= base;
		base *= base;
		exp /= 2;
	}
	return (res);
}

inline Real	sqrt( Real x )
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

}