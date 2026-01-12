/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VariableNode.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:25:19 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/12 15:36:25 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BaseNode.hpp"

struct VariableNode final : BaseNode
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