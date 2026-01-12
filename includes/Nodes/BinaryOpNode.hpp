/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinaryOpNode.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:23:47 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/12 15:52:23 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BaseNode.hpp"
#include "Visitors.hpp"

struct BinaryOpNode final : BaseNode
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
