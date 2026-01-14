/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinaryOpNode.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:23:47 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/14 10:30:10 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BaseNode.hpp"
#include "Visitors.hpp"

class BinaryOpNode : public BaseNode
{
	private:
		OpKind	op;
		NodePtr	left, right;

	public:
		BinaryOpNode( OpKind, NodePtr, NodePtr );
		
		NodePtr	clone() const override;
		VarType	eval( Context& ) const override;
};
