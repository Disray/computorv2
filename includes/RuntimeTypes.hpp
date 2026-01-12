/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RuntimeTypes.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:39:07 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/12 15:43:05 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>
#include <variant>

#include "Types/Complex.hpp"
#include "Types/Matrix.hpp"
#include "Types/Real.hpp"
#include "Types/Token.hpp"

using VarType = std::variant<Real, Complex, Matrix>;
using Context = std::map<std::string, VarType>;