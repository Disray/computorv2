/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FunctionCallNode.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:57:22 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/14 14:13:06 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BaseNode.hpp"

class FunctionCallNode : public BaseNode
{
	private:
		std::string	name;
		NodePtr		arg;

	public:
		FunctionCallNode( std::string, NodePtr );

		NodePtr	clone() const override;
		VarType	eval( Context& ) const override;
};
