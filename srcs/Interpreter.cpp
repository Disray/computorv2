/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Interpreter.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:13:06 by rrichard          #+#    #+#             */
/*   Updated: 2026/02/12 20:43:28 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Interpreter.hpp"
#include <type_traits>

Interpreter::Interpreter( Context& ctx ) : _ctx(ctx) {}

Interpreter::~Interpreter() {}

int		Interpreter::findEqualIndex( const std::vector<Token>& tokens ) const
{
	for (size_t i = 0; i < tokens.size(); i++)
	{
		if (tokens[i].type == TokenType::EQUAL)
			return (static_cast<int>(i));
	}
	return (-1);
}

void	Interpreter::printVarType( const VarType& v, const std::string& polyVar ) const
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

Target	Interpreter::parseLHS( const std::vector<Token>& tokens ) const
{
	if (tokens.size() == 1 && tokens[0].type == TokenType::VARIABLE)
		return (Target(tokens[0], Token("", TokenType::UNKOWN, Arity::CONSTANT, OpKind::NONE), false));
	if (tokens.size() == 4 && 
		tokens[0].type == TokenType::VARIABLE &&
		tokens[1].type == TokenType::BRACKET_OPEN &&
		(tokens[2].type == TokenType::VARIABLE || tokens[2].type == TokenType::NUMBER) &&
		tokens[3].type == TokenType::BRACKET_CLOSE)
	{
		return (Target(tokens[0], tokens[2], true));
	}
	throw std::runtime_error("Syntax Error: Left side must be a variable or function declaration.");
}

void	Interpreter::executeQuery( const Target& target, const std::vector<Token>& rhsTokens ) const
{
	auto it = _ctx.find(target.name.value);
	if (it == _ctx.end())
		throw std::runtime_error("Unknown variable or function: " + target.name.value);

	if (!rhsTokens.empty())
	{
		if (!target.isFunction)
			throw std::runtime_error("Cannot evaluate an expression on a simple variable. Did you mean '==' ?");

		const Polynomial*	poly = std::get_if<Polynomial>(&it->second);
		if (!poly)
			throw std::runtime_error(target.name.value + " is not a polynomial function.");

		Parser	parser(rhsTokens);
		VarType	rhsResult = parser.parse()->eval(_ctx);
		
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
			if (target.param.type == TokenType::NUMBER)
			auto	itParam = _ctx.find(target.param.value);
			if (itParam == _ctx.end())
				throw std::runtime_error("Parameter '" + target.param.value + "' is not defined in context.");

			const Polynomial*	poly = std::get_if<Polynomial>(&it->second);

			if (!poly)
				throw std::runtime_error(target.name.value + " is not a polynomial function.");
			printVarType(poly->eval(itParam->second));
		}
		else
			printVarType(it->second);
	}
}

void	Interpreter::executeAssignment( const Target& target, const std::vector<Token>& rhsTokens )
{
	Context evalCtx = _ctx;

	if (target.isFunction)
		evalCtx[target.param.value] = Polynomial({0, 1});

	Parser	parser(rhsTokens);
	VarType	result = parser.parse()->eval(evalCtx);

	if (target.isFunction && !std::holds_alternative<Polynomial>(result))
		throw std::runtime_error("Function must evaluate to a Polynomial");

	_ctx[target.name.value] = result;

	std::cout << target.name.value;
	if (target.isFunction)
		std::cout << "(" << target.param.value << ")";
	std::cout << " = ";
	printVarType(result);
}

void	Interpreter::processLine( std::vector<Token>& tokens )
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

	int eq = findEqualIndex(tokens);

	if (eq == -1)
	{
		Parser parser(tokens);
		VarType result = parser.parse()->eval(_ctx);
		printVarType(result);
		return;
	}

	std::vector<Token>	lhsTokens(tokens.begin(), tokens.begin() + eq);
	std::vector<Token>	rhsTokens(tokens.begin() + eq + 1, tokens.end());

	Target				target = parseLHS(lhsTokens);

	if (isQuery)
		executeQuery(target, rhsTokens);
	else
		executeAssignment(target, rhsTokens);
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