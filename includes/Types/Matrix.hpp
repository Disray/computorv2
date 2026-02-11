/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:28:09 by rrichard          #+#    #+#             */
/*   Updated: 2026/02/04 12:30:42 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <iostream>
#include <concepts>

#include "Real.hpp"
#include "Complex.hpp"

template<typename K>
concept real_complex = 
	std::same_as<K, Real> ||
	std::same_as<K, Complex>;

template<real_complex K>
class Matrix
{
	private:
		std::vector<K> elements;
		size_t			_rows;
		size_t			_cols;
	
	public:
		// Square matrix constructor
		Matrix( size_t n );
		// Rectangle matrix constructor
		Matrix( size_t n, size_t m );
		Matrix( std::initializer_list<std::initializer_list<K>> values );
		Matrix( const std::vector<std::vector<K>>& values );
		Matrix( const Matrix& other ) = default;
		Matrix& operator=( const Matrix& other ) = default;	
		~Matrix() = default;
		
		size_t					getSize() const;
		size_t					getRows() const;
		size_t					getCols() const;
		bool					empty() const;
		Matrix<K>				identity() const;
		K&						at( size_t row, size_t col );
		const K&				at( size_t row, size_t col ) const;
		K&						operator()( size_t row, size_t col );
		const K&				operator()( size_t row, size_t col ) const;
		K&						operator[]( size_t index );
		const K&				operator[]( size_t index ) const;

		template<real_complex T>
		friend std::ostream&	operator<<( std::ostream& os, const Matrix<T>& m );

		void					add( const Matrix& m );
		void					sub( const Matrix& m );
		void					scl( const Real& scalar );
		Matrix<K>				mul_mat( const Matrix<K>& mat ) const;
		Matrix<K>				pow( int exp ) const;

		Matrix					operator+( const Matrix& ) const;
		Matrix					operator-( const Matrix& ) const;
		Matrix					operator-() const;
		Matrix					operator*( const Matrix& ) const;
		Matrix					operator*( const Real& scalar ) const;
};

#include "Matrix.tpp"