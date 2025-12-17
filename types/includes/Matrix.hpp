/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:28:09 by rrichard          #+#    #+#             */
/*   Updated: 2025/12/17 12:06:19 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <sstream>
#include <optional>

class Matrix
{
	private:
		std::vector<double> elements;
		size_t				_rows;
		size_t				_cols;
	
	public:
		// Square matrix constructor
		Matrix( size_t n );
		// Rectangle matrix constructor
		Matrix( size_t n, size_t m );
		Matrix( std::initializer_list<std::initializer_list<double>> values );
		Matrix( const Matrix& other ) = default;
		Matrix& operator=( const Matrix& other ) = default;	
		~Matrix() = default;
		
		size_t					getSize() const;
		size_t					getRows() const;
		size_t					getCols() const;
		bool					empty() const;
		double					at( size_t	row, size_t col );
		const double			at( size_t	row, size_t col ) const;
		double					operator()( size_t row, size_t col );
		const double			operator()( size_t row, size_t col ) const;
		double					operator[]( size_t index );
		const double			operator[]( size_t index ) const;

		friend std::ostream&	operator<<( std::ostream& os, const Matrix& m );

		// ex00
		void					add( const Matrix& m );
		void					sub( const Matrix& m );
		void					scl( const double scalar );
};
