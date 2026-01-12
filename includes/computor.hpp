/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 09:40:35 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/12 10:43:37 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>
#include <stdexcept>
#include <variant>
#include <iostream>
#include <vector>
#include "Complex.hpp"
#include "Matrix.hpp"
#include "Real.hpp"

enum class TokenType
{
	NUMBER,
	VARIABLE,
	IMAGINARY,
	OPERATOR,
	BRACKET_OPEN,
	BRACKET_CLOSE,
	COMMA,
	SEMICOLON,
	UNKOWN
};

enum class Arity
{
	CONSTANT,
	UNARY,
	BINARY
};

enum class OpKind
{
	ADD,
	SUB,
	MULT,
	DIV,
	MOD,
	EQUAL	
};

struct Token
{
	std::string	value;
	TokenType	type;
	Arity		arity;
};

using VarType = std::variant<Real, Complex, Matrix>;
using Context = std::map<std::string, VarType>;

std::vector<Token>	lexer( const std::string&  );
void				parser( const std::vector<Token>&, std::map<std::string, VarType>& );
void				pre_pass_arity( std::vector<Token>& );
void				pre_pass_impl_multi( std::vector<Token>& );
