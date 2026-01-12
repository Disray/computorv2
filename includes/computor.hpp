/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 09:40:35 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/12 15:14:12 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <stdexcept>
#include <variant>
#include <iostream>
#include <vector>
#include "Complex.hpp"
#include "Matrix.hpp"
#include "Real.hpp"
#include "Token.hpp"

using VarType = std::variant<Real, Complex, Matrix>;
using Context = std::map<std::string, VarType>;

std::vector<Token>	lexer( const std::string&  );
void				parse_and_assign( const std::vector<Token>&, Context& );
void				pre_pass_arity( std::vector<Token>& );
void				pre_pass_impl_multi( std::vector<Token>& );
