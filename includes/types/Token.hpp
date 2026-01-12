/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:35:53 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/12 14:55:43 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <string>

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

	explicit Token( const std::string& v, const TokenType& t, const Arity& a ) : value(v), type(t), arity(a) {}
};
