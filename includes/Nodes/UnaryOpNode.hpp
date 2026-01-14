/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UnaryOpNode.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:24:32 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/14 10:39:17 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BaseNode.hpp"
#include "Visitors.hpp"

class UnaryOpNode : public BaseNode
{
	private:
		OpKind	op;
		NodePtr	child;

	public:
		UnaryOpNode( OpKind, NodePtr );

		NodePtr	clone() const override;
		VarType	eval( Context& ctx ) const override;
};
