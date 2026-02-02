#pragma once

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

}