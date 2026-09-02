#pragma once

#include "RuntimeTypes.hpp"

struct BinaryOpVisitor
{
	OpKind	value;

	VarType	operator()( const Real&, const Real& ) const;
	VarType operator()( const Complex&, const Real& ) const;
	VarType	operator()( const Real&, const Complex& ) const;
	VarType	operator()( const Complex&, const Complex& ) const;

	VarType operator()( const Matrix<Real>&, const Matrix<Real>& ) const;
	VarType operator()( const Matrix<Complex>&, const Matrix<Complex>& ) const;
	VarType operator()( const Real&, const Matrix<Real>& ) const;
	VarType operator()( const Matrix<Real>&, const Real& ) const;
	VarType operator()( const Real&, const Matrix<Complex>& ) const;
	VarType operator()( const Matrix<Complex>&, const Real& ) const;
	
	VarType	operator()( const Polynomial&, const Polynomial& ) const;
	VarType	operator()( const Real&, const Polynomial& ) const;
	VarType	operator()( const Polynomial&, const Real& ) const;

	template<typename T, typename U>
	VarType operator()( const T&, const U& ) const;
};
