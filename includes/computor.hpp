/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 09:40:35 by rrichard          #+#    #+#             */
/*   Updated: 2026/02/05 21:06:26 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include "RuntimeTypes.hpp"

std::vector<Token>	lexer( const std::string&  );
void				process_line( std::vector<Token>&, Context& );
void				pre_pass_arity( std::vector<Token>& );
void				pre_pass_impl_multi( std::vector<Token>& );
