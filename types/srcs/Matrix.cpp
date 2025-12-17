/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:10:48 by rrichard          #+#    #+#             */
/*   Updated: 2025/12/17 12:08:18 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Matrix.hpp"

Matrix::Matrix( size_t rows, size_t cols )
{
	this->elements = std::vector<double>((rows * cols), 0.0);
	this->_rows = rows;
	this->_cols = cols;
}

Matrix::Matrix( std::initializer_list<std::initializer_list<double>> values )
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

Matrix::Matrix( size_t n )
{
	this->elements = std::vector<double>(n * n, 0.0);
	this->_rows = n;
	this->_cols = n;
}

size_t			Matrix::getSize() const
{
	return (this->_cols * this->_rows);
}

size_t			Matrix::getRows() const
{
	return (this->_rows);
}

size_t			Matrix::getCols() const
{
	return (this->_cols);
}

bool			Matrix::empty() const
{
	return (elements.empty());
}

double			Matrix::at( size_t row, size_t col )
{
	if (row >= this->_rows || col >= this->_cols)
		throw std::out_of_range("Matrix::at: index out of range: ");
	return (elements[row * _cols + col]);
}

const double	Matrix::at( size_t row, size_t col ) const
{
	if (row >= this->_rows || col >= this->_cols)
		throw std::out_of_range("Matrix::at: index out of range: ");
	return (elements[row * _cols + col]);
}

double			Matrix::operator()( size_t row, size_t col )
{
	return (at(row, col));
}

const double	Matrix::operator()( size_t row, size_t col ) const
{
	return (at(row, col));
}

double			Matrix::operator[]( size_t index )
{
	if (index >= this->getSize())
		throw std::runtime_error("Error: index out of bound.");
	return (this->elements[index]);
}

const double	Matrix::operator[]( size_t index ) const
{
	if (index >= this->getSize())
		throw std::runtime_error("Error: index out of bound.");
	return (this->elements[index]);
}

std::ostream&	operator<<( std::ostream& os, const Matrix& m )
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