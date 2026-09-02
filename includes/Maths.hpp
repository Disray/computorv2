#pragma once

#include "Real.hpp"
#include "Types/Complex.hpp"

namespace maths
{

	inline constexpr double pi = 3.14159265358979323846;
	inline constexpr double e = 2.71828182845904523536;
	inline constexpr double sqrt2 = 1.41421356237309504880;

	Real		min( const Real&, const Real& );
	Real		max( const Real&, const Real& );
	Real		abs( const Real& );
	Real		abs( const Complex& );
	double		abs( double );
	Real		pow( const Real&, int );
	Complex		pow( const Complex&, int );
	bool		finite( double );
	int			round( double );
	Real		scalar_norm2( const Real& );
	Real		scalar_norm2( const Complex& );
	int			gcd( int, int );
	double		floor( double );

	Real		exp( const Real& x, size_t terms = 50 );
	Complex		exp( const Complex& z, size_t terms = 50 );
	Real		sqrt( const Real& );
	Complex		sqrt( const Complex& );

	Real		cos( const Real& x, size_t terms = 50 );
	Complex		cos( const Complex& z, size_t terms = 50 );
	Real		sin( const Real& r, size_t terms = 50 );
	Complex		sin( const Complex& z, size_t terms = 50 );
	Real		tan( const Real& x, size_t terms = 50 );
	Complex		tan( const Complex& z, size_t terms = 50 );
	Real		arctan( const Real& x, size_t terms = 50 );
	Real		arctan2( const Real& a, const Real& b );

}
