/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MatrixNode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:54:46 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/12 18:16:27 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BaseNode.hpp"

class MatrixNode : BaseNode
{
	private:
		std::vector<std::vector<NodePtr>>	elements;
	
	public:
		explicit MatrixNode( std::vector<std::vector<NodePtr>> elems ) : elements(std::move(elems)) {}
		
		VarType eval( Context& ctx ) const override
		{
			std::vector<std::vector<VarType>>	values;
			
			for (const auto& row : elements)
			{
				std::vector<VarType>	vrow;
				for (const auto& expr : row)
					vrow.push_back(expr->eval(ctx));
				values.push_back(std::move(vrow));
			}
			return (Matrix(values));
		}
};