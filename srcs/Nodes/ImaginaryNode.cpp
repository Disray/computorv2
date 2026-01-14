/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ImaginaryNode.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 10:52:45 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/14 10:53:18 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ImaginaryNode.hpp"

NodePtr	ImaginaryNode::clone() const
{
	return (std::make_unique<ImaginaryNode>());
}

VarType	ImaginaryNode::eval( Context& ) const
{
	return (Complex(0, 1));
}