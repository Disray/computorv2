#pragma once

#include <iostream>
#include "Types/Real.hpp"

class Complex
{
	private:
		Real	real;
		Real	imag;
	
	public:
		Complex();
		Complex( Real, Real );
		Complex( Real );
		Complex( const Complex& ) = default;
		~Complex() = default;
		
		Complex		conj() const;
		Real		abs() const;
		Real		getReal() const;
		Real		getImag() const;
		void		setReal( Real );
		void		setImag( Real );

		Complex		pow( int ) const;
		
		Complex		operator+( const Complex& ) const noexcept;
		Complex&	operator+=( const Complex& ) noexcept;

		Complex		operator-( const Complex& ) const noexcept;
		Complex		operator-() const;
		Complex&	operator-=( const Complex& ) noexcept;

		Complex		operator*( const Complex& ) const noexcept;
		Complex&	operator*=( const Complex& ) noexcept;
		
		Complex		operator/( const Complex& ) const noexcept;
		Complex&	operator/=( const Complex& ) noexcept;

		Complex&	operator=( const Complex& ) = default;
		bool		operator==( const Complex& ) const noexcept;

		friend std::ostream&	operator<<( std::ostream&, const Complex& );
};

Complex	operator+( const Complex&, const Real& );
Complex	operator+( const Real&, const Complex& );
Complex	operator-( const Complex&, const Real& );
Complex	operator-( const Real&, const Complex& );
Complex	operator*( const Complex&, const Real& );
Complex	operator*( const Real&, const Complex& );
Complex	operator/( const Complex&, const Real& );
Complex	operator/( const Real&, const Complex& );
