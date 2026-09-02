#pragma once

#include "RuntimeTypes.hpp"

struct UnaryOpVisitor
{
	OpKind	value;

	VarType	operator()( const Real& )    const;
	VarType	operator()( const Complex& ) const;
	VarType	operator()( const Matrix<Real>& )  const;
	VarType	operator()( const Matrix<Complex>& )  const;
	VarType	operator()( const Polynomial& ) const;
};
