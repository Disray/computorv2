/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MatrixNode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:54:46 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/14 10:54:50 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BaseNode.hpp"

class MatrixNode : public BaseNode
{
	private:
		std::vector<std::vector<NodePtr>>	elements;
	
	public:
		explicit MatrixNode( std::vector<std::vector<NodePtr>> );
		
		NodePtr	clone() const override;
		VarType eval( Context& ctx ) const override;
};