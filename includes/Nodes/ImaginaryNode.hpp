/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ImaginaryNode.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:25:50 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/12 15:36:16 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BaseNode.hpp"

struct ImaginaryNode final : BaseNode
{
	NodePtr	clone() const override
	{
		return (std::make_unique<ImaginaryNode>());
	}
	VarType	eval( Context& ) const override
	{
		return (Complex(0, 1));
	}
};
