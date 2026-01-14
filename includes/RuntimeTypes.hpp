/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RuntimeTypes.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:39:07 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/14 14:55:39 by rrichard         ###   ########.fr       */
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
#include "Types/Polynomial.hpp"

using VarType = std::variant<Real, Complex, Polynomial, Matrix<Real>, Matrix<Complex>>;
using Context = std::map<std::string, VarType>;