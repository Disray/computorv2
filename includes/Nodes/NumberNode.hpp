/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumberNode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:22:58 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/14 10:50:45 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BaseNode.hpp"
#include "Types/Real.hpp"

class NumberNode : public BaseNode
{
	private:
		Real	value;

	public:
		explicit NumberNode( Real );

		NodePtr	clone() const override;
		VarType	eval( Context& ) const override;
};
