#pragma once

#include <iostream>
#include <exception>
#include <compare>

class Real
{
	private:
		double	value;
	
	public:
		Real();
		Real( double );
		Real( const Real& ) = default;
		~Real() = default;

		Real					operator+( const Real& ) const noexcept;
		Real					operator-( const Real& ) const noexcept;
		Real					operator*( const Real& ) const noexcept;
		Real					operator/( const Real& ) const;
		Real					operator-() const noexcept;
		Real&					operator=( const Real& ) = default;
		Real&					operator+=( const Real& ) noexcept;
		Real&					operator-=( const Real& ) noexcept;
		Real&					operator*=( const Real& ) noexcept;
		Real&					operator/=( const Real& );
		bool					operator==( const Real& ) const noexcept;
		auto					operator<=>( const Real& ) const = default;
		Real					operator%( const Real& ) const;

		explicit				operator long() const;
		explicit				operator double() const;
		explicit				operator int() const;

		friend std::ostream&	operator<<( std::ostream&, const Real& );

		double					getValue() const;
		Real					square() const noexcept;
		Real					abs() const;
};
