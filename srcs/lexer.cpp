/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 10:28:38 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/09 10:36:30 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.hpp"
#include <regex>
#include <cctype>

std::vector<Token>	lexer( const std::string& input )
{
	const std::regex 	pattern("([0-9]+(\\.[0-9]+)?)|([a-zA-Z][a-zA-Z0-9_]*)|([\\+\\-\\*\\/%\\(\\)=])");
	auto				words_begin = std::sregex_iterator(input.begin(), input.end(), pattern);
	auto				words_end	= std::sregex_iterator();
	std::vector<Token>	tokens;

	for (std::sregex_iterator i = words_begin; i != words_end; i++)
	{
		std::smatch	match = *i;
		std::string	match_str = match.str();
		TokenType	type = UNKOWN;

		if (isdigit(match_str[0]))
			type = NUMBER;
		else if (isalpha(match_str[0]))
		{
			if (match_str == "i")
				type = IMAGINARY;
			else
				type = VARIABLE;
		}
		else
			type = OPERATOR;
		tokens.push_back({match_str, type, CONSTANT});
	}
	return (tokens);
}