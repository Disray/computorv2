/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UnaryOpNode.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:24:32 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/12 15:52:36 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BaseNode.hpp"
#include "Visitors.hpp"

struct UnaryOpNode final : BaseNode
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
