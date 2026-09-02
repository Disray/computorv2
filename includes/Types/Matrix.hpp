#pragma once

#include <vector>
#include <iostream>
#include <concepts>
#include <optional>

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
		Real					norm() const;
		
		void					swap_rows( size_t, size_t );
		void					scale_row( size_t, K );
		void					add_row_multiple( size_t, size_t, K );
		size_t					findIndexMaxAbsColumn( size_t col, size_t start_row );
		std::optional<Matrix<K>>	inverse() const;
		

		Matrix					operator+( const Matrix& ) const;
		Matrix					operator-( const Matrix& ) const;
		Matrix					operator-() const;
		Matrix					operator*( const Matrix& ) const;
		Matrix					operator*( const Real& scalar ) const;
};

#include "Matrix.tpp"
