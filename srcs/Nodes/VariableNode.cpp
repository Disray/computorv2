/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VariableNode.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 10:39:58 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/14 10:50:56 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VariableNode.hpp"

VariableNode::VariableNode( std::string n ) : name(std::move(n)) {}

NodePtr	VariableNode::clone() const
{
	return (std::make_unique<VariableNode>(name));
}

VarType	VariableNode::eval( Context& ctx ) const
{
	if (!ctx.contains(name))
		throw std::runtime_error("Undefined variable: " + name);

	return (ctx.at(name));
}
