/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:09:02 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/09 14:30:37 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <map>
#include <variant>
#include <regex>
#include "computor.hpp"

int	main( void )
{
	std::string						input;
	std::map<std::string, VarType>	variables;

	while (true)
	{
		getline(std::cin, input);
		try
		{
			auto	tokens = lexer(input);

			pre_pass_arity(tokens);
			pre_pass_impl_multi(tokens);
			// for (auto& i : tokens)
			// 	std::cout << i.value << " | " << i.type << " | " << i.arity << std::endl;
			process_input(tokens, variables);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	return (0);
}
