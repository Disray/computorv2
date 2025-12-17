/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:09:02 by rrichard          #+#    #+#             */
/*   Updated: 2025/12/17 11:43:36 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/includes/Complex.hpp"
#include "types/includes/Real.hpp"
#include <string>

int	main( void )
{
	std::string	input;

	getline(std::cin, input);
	try
	{
		//parser
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}