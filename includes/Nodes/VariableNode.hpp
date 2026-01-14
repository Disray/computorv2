/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VariableNode.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:25:19 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/14 10:51:03 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BaseNode.hpp"

class VariableNode : public BaseNode
{
	private:
		std::string	name;
	
	public:
		explicit VariableNode( std::string );

		NodePtr	clone() const override;
		VarType	eval( Context& ) const override;
};
