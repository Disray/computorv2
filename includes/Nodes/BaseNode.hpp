/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseNode.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 09:51:58 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/14 10:59:22 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include "RuntimeTypes.hpp"

class BaseNode;
using NodePtr = std::unique_ptr<BaseNode>;

class BaseNode
{
	public:
		virtual ~BaseNode() = default;

		virtual	NodePtr	clone() const = 0;
		virtual VarType	eval( Context& ) const = 0;
};
