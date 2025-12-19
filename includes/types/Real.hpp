/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Real.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:57:52 by rrichard          #+#    #+#             */
/*   Updated: 2025/12/19 10:33:16 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <exception>

class Real
{
	private:
		double	real;
	
	public:
		Real();
		Real( double );
		Real( const Real& ) = default;
		~Real() = default;

		Real		operator+( const Real& ) const noexcept;
		Real		operator-( const Real& ) const noexcept;
		Real		operator*( const Real& ) const noexcept;
		Real		operator/( const Real& ) const;
		Real		operator-() const noexcept;
		Real&		operator=( const Real& ) = default;
		Real&		operator+=( const Real& ) noexcept;
		Real&		operator-=( const Real& ) noexcept;
		Real&		operator*=( const Real& ) noexcept;
		Real&		operator/=( const Real& );
		bool		operator==( const Real& ) const noexcept;

		double		getReal() const;
};