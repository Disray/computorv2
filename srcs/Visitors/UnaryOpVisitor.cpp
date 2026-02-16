
#include "Visitors/UnaryOpVisitor.hpp"

VarType	UnaryOpVisitor::operator()( const Real& a ) const
{
	switch (value)
	{
		case OpKind::ADD: return (a);
		case OpKind::SUB: return (-a);
		default:
			throw std::runtime_error("Unknown unary operator");
	}
}

VarType	UnaryOpVisitor::operator()( const Complex& c ) const
{
	switch (value)
	{
		case OpKind::ADD: return (c);
		case OpKind::SUB: return (-c);
		default:
			throw std::runtime_error("Unknown unary operator");
	}
}

VarType	UnaryOpVisitor::operator()( const Matrix<Real>& m ) const
{
	switch (value)
	{
		case OpKind::ADD: return (m);
		case OpKind::SUB: return (-m);
		default:
			throw std::runtime_error("Unknown unary operator");	
	}
}

VarType	UnaryOpVisitor::operator()( const Matrix<Complex>& m ) const
{
	switch (value)
	{
		case OpKind::ADD: return (m);
		case OpKind::SUB: return (-m);
		default:
			throw std::runtime_error("Unknown unary operator");	
	}
}

VarType	UnaryOpVisitor::operator()( const Polynomial& ) const
{
	throw std::runtime_error("Invalid unary operator");
}

VarType	apply_unary_op( const OpKind& op, const VarType& a )
{
	return (std::visit(UnaryOpVisitor{op}, a));
}
