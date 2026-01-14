/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MatrixNode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 10:53:54 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/14 10:56:58 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MatrixNode.hpp"

MatrixNode::MatrixNode( std::vector<std::vector<NodePtr>> elems ) : elements(std::move(elems)) {}

NodePtr	MatrixNode::clone() const
{
	std::vector<std::vector<NodePtr>>	cloned;
	cloned.reserve(elements.size());

	for (const auto& row : elements)
	{
		std::vector<NodePtr>	crow;

		crow.reserve(row.size());
		for (const auto& expr : row)
			crow.push_back(expr ? expr->clone() : nullptr);
		cloned.push_back(std::move(crow));
	}
	return (std::make_unique<MatrixNode>(std::move(cloned)));
}

VarType MatrixNode::eval( Context& ctx ) const
{
	std::vector<std::vector<VarType>>	values;
	bool								hasComplex = false;
	
	for (const auto& row : elements)
	{
		std::vector<VarType>	vrow;

		for (const auto& expr : row)
		{
			VarType	v = expr->eval(ctx);
			if (std::holds_alternative<Complex>(v))
				hasComplex = true;
			else if (!std::holds_alternative<Real>(v))
				throw std::runtime_error("Matrix elements must be Real or Complex");
			vrow.push_back(std::move(v));
		}
		values.push_back(std::move(vrow));
	}
	if (!hasComplex)
	{
		std::vector<std::vector<Real>>	out;

		out.reserve(values.size());
		for (const auto& row : values)
		{
			std::vector<Real> orow;

			orow.reserve(row.size());
			for (const auto& v : row)
				orow.push_back(std::get<Real>(v));
			out.push_back(std::move(orow));
		}
		return (Matrix<Real>(out));
	}
	
	std::vector<std::vector<Complex>>	out;

	out.reserve(values.size());
	for (const auto& row : values)
	{
		std::vector<Complex>	orow;

		orow.reserve(row.size());
		for (const auto& v : row)
		{
			if (std::holds_alternative<Complex>(v))
				orow.push_back(std::get<Complex>(v));
			else
				orow.push_back(Complex(std::get<Real>(v).getReal(), 0.));
		}
		out.push_back(std::move(orow));
	}
	return (Matrix<Complex>(out));
}