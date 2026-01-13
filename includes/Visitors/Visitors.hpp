/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Visitors.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:47:39 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/13 11:30:16 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "RuntimeTypes.hpp"

VarType	apply_unary_op( const OpKind&, const VarType& );
VarType	apply_binary_op( const OpKind&, const VarType&, const VarType& );
