/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumberNode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 10:42:23 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/14 10:50:53 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NumberNode.hpp"

NumberNode::NumberNode( Real v ) : value(v) {}

NodePtr	NumberNode::clone() const
{
	return (std::make_unique<NumberNode>(value));
}

VarType	NumberNode::eval( Context& ) const
{
	return (value);
}
