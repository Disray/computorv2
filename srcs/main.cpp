/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:09:02 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/12 14:53:42 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <map>
#include <variant>
#include <regex>
#include "Parser.hpp"

int	main( void )
{
	std::string	input;
	Context		ctx;

	while (true)
	{
		getline(std::cin, input);
		try
		{
			auto	tokens = lexer(input);
			pre_pass_arity(tokens);
			pre_pass_impl_multi(tokens);

			Parser	parser(tokens);
			auto	ast = parser.parse();
			VarType	result = ast->eval(ctx);
			std::visit([](const auto& v)
			{
				std::cout << v << std::endl;
			}, result);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	return (0);
}
