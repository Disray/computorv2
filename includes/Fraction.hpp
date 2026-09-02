#pragma once

#include <iostream>

class Fraction
{
	private:
		int	numerator, denominator;

	public:
		Fraction( int num, int den = 1 );
		Fraction& operator=( const Fraction& other ) = default;
		Fraction( const Fraction& other ) = default;
		~Fraction() = default;

		void					simplify();	
		void					print() const;
		int						getNum() const;
		int						getDenom() const;
		friend std::ostream&	operator<<( std::ostream& os, const Fraction& f );
		static bool				fromDouble( double value, Fraction& out );
};
