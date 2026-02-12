/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:35:53 by rrichard          #+#    #+#             */
/*   Updated: 2026/02/12 19:20:18 by rrichard         ###   ########.fr       */
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
	EQUAL,
	BRACKET_OPEN,
	BRACKET_MATRIX_OPEN,
	BRACKET_CLOSE,
	BRACKET_MATRIX_CLOSE,
	COMMA,
	SEMICOLON,
	QUERY,
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
	MUL,
	DIV,
	MOD,
	POW,
	MUL_MAT,
	NONE	
};

struct Token
{
	std::string	value;
	TokenType	type;
	Arity		arity;
	OpKind		op;

	Token( const std::string& v, const TokenType& t, const Arity& a, const OpKind& o ) : value(v), type(t), arity(a), op(o) {}
};
