/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:09:02 by rrichard          #+#    #+#             */
/*   Updated: 2026/02/12 20:04:40 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <map>
#include <variant>
#include <regex>
#include "computor.hpp"
#include "Interpreter.hpp"
#include "Lexer.hpp"

int	main( void )
{
	std::string	input;
	Context		ctx;
	Interpreter	interpret(ctx);
	Lexer		lexer;

	while (true)
	{
		getline(std::cin, input);
		try
		{
			auto	tokens = lexer.tokenize(input);
			interpret.processLine(tokens);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	return (0);
}
