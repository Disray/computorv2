/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:09:02 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/21 17:25:30 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <map>
#include <variant>
#include <regex>
#include "computor.hpp"

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
			parse_and_assign(tokens, ctx);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	return (0);
}
