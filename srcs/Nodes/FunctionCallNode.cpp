/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FunctionCallNode.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:13:15 by rrichard          #+#    #+#             */
/*   Updated: 2026/02/12 18:47:21 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FunctionCallNode.hpp"

FunctionCallNode::FunctionCallNode( std::string n, NodePtr a ) : name(std::move(n)), arg(std::move(a)) {}

NodePtr	FunctionCallNode::clone() const
{
	return (std::make_unique<FunctionCallNode>(name, arg ? arg->clone() : nullptr));
}

VarType	FunctionCallNode::eval( Context& ctx ) const
{
	if (!arg)
		throw std::runtime_error("Invalid function call");

	VarType	x = arg->eval(ctx);
	auto	it = ctx.find(name);

	if (it == ctx.end())
		throw std::runtime_error("Unkown function");

	const Polynomial*	p = std::get_if<Polynomial>(&it->second);
	if (!p)
		throw std::runtime_error("Not a function");

	if (const Real* r = std::get_if<Real>(&x))
		return (p->eval(*r));
	if (const Complex* z = std::get_if<Complex>(&x))
		return (p->eval(*z));
	if (const Polynomial* poly = std::get_if<Polynomial>(&x))
		return (p->eval(*poly));
	throw std::runtime_error("Invalid function argument type");
}
