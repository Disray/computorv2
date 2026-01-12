/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumberNode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:22:58 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/12 15:36:19 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BaseNode.hpp"

struct NumberNode final : BaseNode
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
