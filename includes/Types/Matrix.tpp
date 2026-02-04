/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:10:48 by rrichard          #+#    #+#             */
/*   Updated: 2026/02/04 11:02:46 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Matrix.hpp"

template<real_complex K>
Matrix<K>::Matrix( size_t rows, size_t cols )
{
	this->elements = std::vector<K>((rows * cols), K(0));
	this->_rows = rows;
	this->_cols = cols;
}

template<real_complex K>
Matrix<K>::Matrix( std::initializer_list<std::initializer_list<K>> values )
{
	if (values.size() == 0)
	{
		_rows = 0;
		_cols = 0;
		elements.clear();
		return ;
	}
	_rows = values.size();
	_cols = values.begin()->size();
	for (const auto& row : values)
	{
		if (row.size() != _cols)
			throw std::runtime_error("Error: inconsistent row size");
	}
	elements.reserve(_rows * _cols);
	for (const auto& row : values)
		elements.insert(elements.end(), row.begin(), row.end());
}

template<real_complex K>
Matrix<K>::Matrix( const std::vector<std::vector<K>>& values )
{
	if (values.size() == 0)
	{
		_rows = 0;
		_cols = 0;
		elements.clear();
		return ;
	}
	_rows = values.size();
	_cols = values.begin()->size();
	for (const auto& row : values)
	{
		if (row.size() != _cols)
			throw std::runtime_error("Error: inconsistent row size");
	}
	elements.reserve(_rows * _cols);
	for (const auto& row : values)
		elements.insert(elements.end(), row.begin(), row.end());
}

template<real_complex K>
Matrix<K>::Matrix( size_t n )
{
	this->elements = std::vector<K>(n * n, K(0));
	this->_rows = n;
	this->_cols = n;
}

template<real_complex K>
size_t			Matrix<K>::getSize() const
{
	return (this->_cols * this->_rows);
}

template<real_complex K>
size_t			Matrix<K>::getRows() const
{
	return (this->_rows);
}

template<real_complex K>
size_t			Matrix<K>::getCols() const
{
	return (this->_cols);
}

template<real_complex K>
bool			Matrix<K>::empty() const
{
	return (elements.empty());
}

template<real_complex K>
K&			Matrix<K>::at( size_t row, size_t col )
{
	if (row >= this->_rows || col >= this->_cols)
		throw std::out_of_range("Matrix::at: index out of range: ");
	return (elements[row * _cols + col]);
}

template<real_complex K>
const K&	Matrix<K>::at( size_t row, size_t col ) const
{
	if (row >= this->_rows || col >= this->_cols)
		throw std::out_of_range("Matrix::at: index out of range: ");
	return (elements[row * _cols + col]);
}

template<real_complex K>
K&			Matrix<K>::operator()( size_t row, size_t col )
{
	return (at(row, col));
}

template<real_complex K>
const K&	Matrix<K>::operator()( size_t row, size_t col ) const
{
	return (at(row, col));
}

template<real_complex K>
K&			Matrix<K>::operator[]( size_t index )
{
	if (index >= this->getSize())
		throw std::runtime_error("Error: index out of bound.");
	return (this->elements[index]);
}

template<real_complex K>
const K&	Matrix<K>::operator[]( size_t index ) const
{
	if (index >= this->getSize())
		throw std::runtime_error("Error: index out of bound.");
	return (this->elements[index]);
}

template<real_complex T>
std::ostream&	operator<<( std::ostream& os, const Matrix<T>& m )
{
	for (size_t i = 0; i < m.elements.size(); i++)
	{
		if (i % m._cols == 0)
			os << "[";
		os << m.elements[i];
		if (i % m._cols == m._cols - 1)
			os << "]" << std::endl;
		else
			os << ", ";
	}
	return (os);
}

template<real_complex K>
void	Matrix<K>::add( const Matrix<K>& m )
{
	if (m._cols != this->_cols || m._rows != this->_rows)
		throw std::runtime_error("Error: Matrices must have the same dimensions for addition");
	for (size_t i = 0; i < elements.size(); i++)
		this->elements[i] += m.elements[i];
}

template<real_complex K>
void	Matrix<K>::sub( const Matrix<K>& m )
{
	if (m._cols != this->_cols || m._rows != this->_rows)
		throw std::runtime_error("Error: Matrices must have the same dimensions for substraction");
	for (size_t i = 0; i < elements.size(); i++)
		this->elements[i] -= m.elements[i];
}

template<real_complex K>
void	Matrix<K>::scl( const Real& scalar )
{
	for (size_t i = 0; i < this->getSize(); i++)
		this->elements[i] *= scalar;
}

template<real_complex K>
Matrix<K>	Matrix<K>::operator+( const Matrix<K>& other ) const
{
	Matrix	m = *this;

	m.add(other);
	return (m);
}

template<real_complex K>
Matrix<K>	Matrix<K>::operator-( const Matrix<K>& other ) const
{
	Matrix	m = *this;

	m.sub(other);
	return (m);
}

template<real_complex K>
Matrix<K>	Matrix<K>::operator-() const
{
	Matrix m = *this;

	m.scl(-1.);
	return (m);
}

template<real_complex K>
Matrix<K>	Matrix<K>::operator*( const Matrix& other ) const
{
	if (this->_cols != other._cols && this->_rows != other._rows)
		throw std::runtime_error("Error: dimensions must be identital for element-wise multiplication");

	Matrix	result(this->_rows, this->_cols);
	
	for (size_t i = 0; i < this->_rows; i++)
		for (size_t j = 0; j < this->_cols; j++)
			result(i, j) = at(i, j) * other(i, j);
	return (result);
}

template<real_complex K>
Matrix<K>	Matrix<K>::operator*( const Real& scalar ) const
{
	Matrix	m = *this;

	m.scl(scalar);
	return (m);
}

template<real_complex K>
Matrix<K>	Matrix<K>::mul_mat( const Matrix<K>& mat ) const
{
	if (this->_cols != mat.getRows())
		throw std::runtime_error("Error: wrong dimensions for matrix multiplication");
		
	Matrix<K>	result(this->_rows, this->_cols);

	for (size_t i = 0; i < this->_rows; i++)
	{
		for (size_t j = 0; j < mat.getCols(); j++)
		{
			K sum = K(0);

			for (size_t h = 0; h < mat.getRows(); h++)
					sum += this->at(i, h) * mat(h, j);
			result(i, j) = sum;
		}
	}
	return (result);
}
