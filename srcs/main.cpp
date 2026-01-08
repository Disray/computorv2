/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:09:02 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/08 15:03:14 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/types.hpp"
#include <string>
#include <map>
#include <variant>
#include <regex>
#include "../includes/computor.hpp"

int	main( void )
{
	std::string						input;
	std::map<std::string, VarType>	variables;

	while (true)
	{
		getline(std::cin, input);
		try
		{
			std::regex 			pattern("([0-9]+(\\.[0-9]+)?)|([a-zA-Z][a-zA-Z0-9_]*)|([\\+\\-\\*\\/%\\(\\)=])");
			auto				words_begin = std::sregex_iterator(input.begin(), input.end(), pattern);
			auto				words_end	= std::sregex_iterator();
			std::vector<Token>	tokenList;
	
			for (std::sregex_iterator i = words_begin; i != words_end; i++)
			{
				std::smatch	match = *i;
				std::string	match_str = match.str();
				TokenType	type = UNKOWN;
	
				if (isdigit(match_str[0]))
					type = NUMBER;
				else if (isalpha(match_str[0]))
					type = VARIABLE;
				else
					type = OPERATOR;
				tokenList.push_back({match_str, type, CONSTANT});
			}
			pre_pass_arity(tokenList);
			process_input(tokenList, variables);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	return (0);
}
