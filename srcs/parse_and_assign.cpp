/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_assign.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:13:06 by rrichard          #+#    #+#             */
/*   Updated: 2026/02/11 17:20:46 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include <type_traits>

int		find_equal_index( const std::vector<Token>& tokens )
{
	for (size_t i = 0; i < tokens.size(); i++)
	{
		if (tokens[i].type == TokenType::EQUAL)
			return (static_cast<int>(i));
	}
	return (-1);
}

void	print_vartype( const VarType& v, const std::string& polyVar = "x" )
{
	std::visit([&](const auto& value)
	{
		using T = std::remove_cvref_t<decltype(value)>;

		if constexpr (std::is_same_v<T, Polynomial>)
			std::cout << value.print(polyVar) << std::endl;
		else
			std::cout << value << std::endl;
	}, v);
}

void	handle_query( const std::string& target, const std::string& param, bool isFunc, Context& ctx )
{
	auto	it = ctx.find(target);
	if (it == ctx.end())
		throw std::runtime_error("Variable or function '" + target + "' is not defined.");

	if (isFunc)
	{
		const Polynomial*	poly = std::get_if<Polynomial>(&it->second);
		if (!poly)
			throw std::runtime_error(target + " is not a function.");
		auto	it_param = ctx.find(param);
		if (it_param == ctx.end())
			throw std::runtime_error("Parameter '" + param + "' has no value assigned.");
		VarType	result = poly->eval(it_param->second);
		print_vartype(result, param.empty() ? "x" : param);
	}
	else
		print_vartype(it->second, "x");
}

Target	parse_lhs( const std::vector<Token>& tokens )
{
	if (tokens.size() == 1 && tokens[0].type == TokenType::VARIABLE)
		return (Target(tokens[0].value, "", false));
	if (tokens.size() == 4 && 
		tokens[0].type == TokenType::VARIABLE &&
		tokens[1].type == TokenType::BRACKET_OPEN &&
		tokens[2].type == TokenType::VARIABLE &&
		tokens[3].type == TokenType::BRACKET_CLOSE)
		return (Target(tokens[0].value, tokens[2].value, true));
	throw std::runtime_error("Syntax Error: Left side must be a variable or function declaration.");
}

void	execute_query( const Target& target, const std::vector<Token>& rhsTokens, Context& ctx )
{
	auto it = ctx.find(target.name);
	if (it == ctx.end())
		throw std::runtime_error("Unknown variable or function: " + target.name);

	if (!rhsTokens.empty())
	{
		if (!target.isFunction)
			throw std::runtime_error("Cannot evaluate an expression on a simple variable. Did you mean '==' ?");

		const Polynomial*	poly = std::get_if<Polynomial>(&it->second);
		if (!poly)
			throw std::runtime_error(target.name + " is not a polynomial function.");

		Parser	parser(rhsTokens);
		VarType	rhsResult = parser.parse()->eval(ctx);
		
		if (std::holds_alternative<Real>(rhsResult))
		{
			Real		val = std::get<Real>(rhsResult);
			Polynomial	equation = *poly;

			equation -= val;
			std::vector<Root>	solutions = equation.solve(true);

			if (solutions.empty())
				std::cout << "No solution" << std::endl;
		}
		else
			throw std::runtime_error("Equation resolution expects a scalar value on the right side.");
	}
	else 
	{
		if (target.isFunction)
		{
			auto	itParam = ctx.find(target.param);
			if (itParam == ctx.end())
				throw std::runtime_error("Parameter '" + target.param + "' is not defined in context.");

			const Polynomial*	poly = std::get_if<Polynomial>(&it->second);

			if (!poly)
				throw std::runtime_error(target.name + " is not a polynomial function.");
			print_vartype(poly->eval(itParam->second));
		}
		else
			print_vartype(it->second);
	}
}

void	execute_assignment( const Target& target, const std::vector<Token>& rhsTokens, Context& ctx )
{
	Context evalCtx = ctx;

	if (target.isFunction)
		evalCtx[target.param] = Polynomial({0, 1});

	Parser	parser(rhsTokens);
	VarType	result = parser.parse()->eval(evalCtx);

	if (target.isFunction && !std::holds_alternative<Polynomial>(result))
		throw std::runtime_error("Function must evaluate to a Polynomial");

	ctx[target.name] = result;

	std::cout << target.name;
	if (target.isFunction)
		std::cout << "(" << target.param << ")";
	std::cout << " = ";
	print_vartype(result);
}

void	process_line( std::vector<Token>& tokens, Context& ctx )
{
	if (tokens.empty())
		return;

	bool isQuery = false;
	if (tokens.back().type == TokenType::QUERY)
	{
		isQuery = true;
		tokens.pop_back();
		if (tokens.empty())
			return;
	}

	int eq = find_equal_index(tokens);

	if (eq == -1)
	{
		Parser parser(tokens);
		VarType result = parser.parse()->eval(ctx);
		print_vartype(result);
		return;
	}

	std::vector<Token>	lhsTokens(tokens.begin(), tokens.begin() + eq);
	std::vector<Token>	rhsTokens(tokens.begin() + eq + 1, tokens.end());

	Target				target = parse_lhs(lhsTokens);

	if (isQuery)
		execute_query(target, rhsTokens, ctx);
	else
		execute_assignment(target, rhsTokens, ctx);
}

// void	parse_and_assign( std::vector<Token>& tokens, Context& ctx )
// {
// 	if (tokens.empty())
// 		return ;

// 	bool	isQuery = (tokens.back().type == TokenType::QUERY);
// 	if (isQuery) tokens.pop_back();

// 	int	eq = find_equal_index(tokens);

// 	if (eq != -1 && (size_t)eq + 1 < tokens.size() && tokens[eq + 1].type == TokenType::QUERY)
// 	{
// 		std::vector<Token>	lhsTokens(tokens.begin(), tokens.begin() + eq);

// 		if (lhsTokens.empty())
// 			throw std::runtime_error("Syntax Error: No expression before '='");

// 		Parser	parser(lhsTokens);
// 		NodePtr	ast = parser.parse();

// 		VarType	result = ast->eval(ctx);
// 		print_vartype(result);
// 		return;
// 	}

// 	std::string			targetName;
// 	std::string			paramName;
// 	std::vector<Token>	expressionToken;
// 	bool				isAssignment = false;
// 	bool				isFunctionAssignment = false;
	
// 	if (eq != -1)
// 	{
// 		if (eq == 1 && tokens[0].type == TokenType::VARIABLE)
// 		{
// 			targetName = tokens[0].value;
// 			isAssignment = true;
// 		}
// 		else if (eq == 4
// 			&& tokens[0].type == TokenType::VARIABLE
// 			&& tokens[1].type == TokenType::BRACKET_OPEN
// 			&& tokens[2].type == TokenType::VARIABLE
// 			&& tokens[3].type == TokenType::BRACKET_CLOSE)
// 		{
// 			targetName = tokens[0].value;
// 			paramName = tokens[2].value;
// 			isAssignment = true;
// 			isFunctionAssignment = true;
// 		}
// 		else
// 			throw std::runtime_error("Syntax Error: Left side of assignment must be a variable");
// 		expressionToken.assign(tokens.begin() + eq + 1, tokens.end());
// 	}
// 	else
// 		expressionToken = tokens;

// 	Parser	parser(expressionToken);
// 	NodePtr	ast = parser.parse();
// 	Context	evalCtx = ctx;

// 	if (isFunctionAssignment)
// 		evalCtx[paramName] = Polynomial({0., 1.});

// 	VarType	result = ast->eval(evalCtx);

// 	if (isAssignment)
// 	{
// 		if (isFunctionAssignment && !std::holds_alternative<Polynomial>(result))
// 			throw std::runtime_error("Function definition must evaluate to a polynomial");
// 		ctx[targetName] = result;
// 		if (isFunctionAssignment)
// 			std::cout << targetName << "(" << paramName << ") = ";
// 		else
// 			std::cout << targetName << " = ";
// 	}
// 	print_vartype(result, (isFunctionAssignment && !paramName.empty()) ? paramName : "x");
// }

// void parse_and_assign(std::vector<Token>& tokens, Context& ctx) {
// 	if (tokens.empty()) return;

// 	// 1. Détection de la requête : est-ce que ça finit par '?'
// 	bool isQuery = (tokens.back().type == TokenType::QUERY);
// 	if (isQuery) tokens.pop_back(); // On enlève le '?' pour ne pas fâcher le Parser

// 	int eq = find_equal_index(tokens);

// 	// ... (Ton code pour extraire targetName, paramName, etc. reste identique) ...

// 	if (isQuery) {
// 		// CAS : funA(x) = y ? ou x = ?
// 		if (eq != -1) {
// 			std::vector<Token> rhsTokens(tokens.begin() + eq + 1, tokens.end());
			
// 			if (rhsTokens.empty()) {
// 				// Cas "f(x) = ?" ou "x = ?" -> On évalue avec la valeur actuelle du paramètre
// 				handle_simple_query(targetName, paramName, isFunctionAssignment, ctx);
// 			} else {
// 				// Cas "f(x) = y ?" -> On évalue la fonction avec la valeur de 'y'
// 				handle_substitution_query(targetName, rhsTokens, ctx);
// 			}
// 		} else {
// 			// Cas "x + 2 ?" (sans égal) -> On évalue juste l'expression
// 			Parser p(tokens);
// 			std::cout << p.parse()->eval(ctx) << std::endl;
// 		}
// 		return;
// 	}

// 	// ... (Reste de ton code pour l'assignation normale) ...
// }