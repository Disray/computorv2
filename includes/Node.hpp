/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 09:51:58 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/12 11:55:53 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <string>
#include "computor.hpp"
#include "Visitors.hpp"

struct Node;
using NodePtr = std::unique_ptr<Node>;

struct Node
{
	virtual ~Node() = default;

	virtual	NodePtr	clone() const = 0;
	virtual VarType	eval( Context& ) const = 0;
};

struct NumberNode final : Node
{
	double	value;

	explicit NumberNode( double v ) : value(v) {}

	NodePtr	clone() const override
	{
		return (std::make_unique<NumberNode>(value));
	}
	VarType	eval( Context& ) const override
	{
		return (Real(value));
	}
};

struct ImaginaryNode final : Node
{
	NodePtr	clone() const override
	{
		return (std::make_unique<ImaginaryNode>());
	}
	VarType	eval( Context& ) const override
	{
		return (Complex(0, 1));
	}
};

struct BinaryOpNode final : Node
{
	OpKind	op;
	NodePtr	left, right;

	explicit BinaryOpNode( OpKind v, NodePtr l, NodePtr r ) : op(v), left(std::move(l)), right(std::move(r)) {}
	
	NodePtr	clone() const override
	{
		return (std::make_unique<BinaryOpNode>(op, left->clone(), right->clone()));
	}
	VarType	eval( Context& ctx ) const override
	{
		VarType	lhs = left->eval(ctx);
		VarType	rhs = right->eval(ctx);

		return (apply_binary_op(op, lhs, rhs));
	}
};

struct UnaryOpNode final : Node
{
	OpKind	op;
	NodePtr	child;

	explicit UnaryOpNode( OpKind v, NodePtr c ) : op(v), child(std::move(c)) {}

	NodePtr	clone() const override
	{
		return (std::make_unique<UnaryOpNode>(op, child->clone()));
	}
	VarType	eval( Context& ctx ) const override
	{
		VarType	value = child->eval(ctx);

		return (apply_unary_op(op, value));
	}
};

struct VariableNode final : Node
{
	std::string	name;
	
	explicit VariableNode( std::string n ) : name(std::move(n)) {}

	NodePtr	clone() const override
	{
		return (std::make_unique<VariableNode>(name));
	}
	VarType	eval( Context& ctx ) const override
	{
		if (!ctx.contains(name))
			throw std::runtime_error("Undefined variable: " + name);

		return (ctx.at(name));
	}
};
