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

}