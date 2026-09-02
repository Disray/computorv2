#pragma once

#include "RuntimeTypes.hpp"

VarType	apply_unary_op( const OpKind&, const VarType& );
VarType	apply_binary_op( const OpKind&, const VarType&, const VarType& );
