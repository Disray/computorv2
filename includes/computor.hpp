/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 09:40:35 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/08 16:11:29 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <string>
#include <stdexcept>
#include <variant>
#include "types.hpp"

enum TokenType
{
	NUMBER,
	VARIABLE,
	OPERATOR,
	UNKOWN
};

enum Arity
{
	CONSTANT,
	UNARY,
	BINARY
};

struct Token
{
	std::string	value;
	TokenType	type;
	Arity		arity;
};

using VarType = std::variant<Real, Complex, Matrix>;

VarType	apply_unary_op( const std::string& op, const VarType& a );
VarType	apply_binary_op( const std::string& op, const VarType& lhs, const VarType& rhs );

void	process_input( const std::vector<Token>&, std::map<std::string, VarType>& );
void	pre_pass_arity( std::vector<Token>& tokens );