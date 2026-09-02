#include "InterpreterEvaluator.hpp"
#include "Parser.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace
{
	struct Target
	{
		std::string	name;
		std::string	param;
		bool		isFunction;

		Target( const std::string& n, const std::string& p, bool f ) : name(n), param(p), isFunction(f) {}
	};

	int	findEqualIndex( const std::vector<Token>& tokens )
	{
		for (size_t i = 0; i < tokens.size(); i++)
		{
			if (tokens[i].type == TokenType::EQUAL)
				return (static_cast<int>(i));
		}
		return (-1);
	}

	Target	parseLHS( const std::vector<Token>& tokens )
	{
		if (tokens.size() == 1 && tokens[0].type == TokenType::VARIABLE)
			return (Target(tokens[0].value, "", false));
		if (tokens.size() == 4 && 
			tokens[0].type == TokenType::VARIABLE 	  &&
			tokens[1].type == TokenType::BRACKET_OPEN &&
			tokens[2].type == TokenType::VARIABLE     &&
			tokens[3].type == TokenType::BRACKET_CLOSE)
		{
			return (Target(tokens[0].value, tokens[2].value, true));
		}
		throw std::runtime_error("Syntax Error: Left side must be a variable or function declaration.");
	}

	void	executeQuery( Context& ctx, const Target& target, const std::vector<Token>& rhsTokens )
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
			
			if (!std::holds_alternative<Real>(rhsResult))
				throw std::runtime_error("Equation resolution expects a scalar value on the right side.");

			Real		val = std::get<Real>(rhsResult);
			Polynomial	equation = *poly;

			equation -= val;
			std::vector<Root>	solutions = equation.solve(true);

			if (solutions.empty())
				std::cout << "No solution" << std::endl;
			return ;
		}
		if (target.isFunction)
		{
			auto	itParam = ctx.find(target.param);

			if (itParam == ctx.end())
				throw std::runtime_error("Parameter '" + target.param + "' is not defined in context.");

			const Polynomial*	poly = std::get_if<Polynomial>(&it->second);

			if (!poly)
				throw std::runtime_error(target.name + " is not a polynomial function.");
			std::cout << poly->eval(itParam->second) << std::endl;
			return ;
		}
		std::cout << it->second << std::endl;
	}

	void	executeAssignment( Context& ctx, std::vector<std::string>& history,
			const Target& target, const std::vector<Token>& rhsTokens, const std::string& rawLine )
	{
		if (Parser::isBuiltinFunction(target.name))
			throw std::runtime_error("Forbidden: '" + target.name + "' is a built-in function and cannot be redefined.");

		Context evalCtx = ctx;

		if (target.isFunction)
			evalCtx[target.param] = Polynomial({0, 1});

		Parser	parser(rhsTokens);
		VarType	result = parser.parse()->eval(evalCtx);

		if (target.isFunction)
		{
			if (std::holds_alternative<Real>(result))
				result = Polynomial({std::get<Real>(result)});

			if (!std::holds_alternative<Polynomial>(result))
				throw std::runtime_error("Function must evaluate to a Polynomial.");
			std::get<Polynomial>(result).setVarName(target.param);
		}

		ctx[target.name] = result;

		std::ostringstream	oss;
		oss << result;
		history.push_back(rawLine + "  ->  " + oss.str());
		std::cout << result << std::endl;
	}
}

namespace interpreter_eval
{
	void	execute( Context& ctx, std::vector<std::string>& history,
			const std::vector<Token>& tokens, bool isQuery, const std::string& rawLine )
	{
		int	eq = findEqualIndex(tokens);

		if (eq == -1)
		{
			Parser	parser(tokens);
			VarType	result = parser.parse()->eval(ctx);
			std::cout << result << std::endl;
			return ;
		}

		std::vector<Token>	lhsTokens(tokens.begin(), tokens.begin() + eq);
		std::vector<Token>	rhsTokens(tokens.begin() + eq + 1, tokens.end());

		if (isQuery)
		{
			if (rhsTokens.empty())
			{
				Parser	parser(lhsTokens);
				std::cout << parser.parse()->eval(ctx) << std::endl;
			}
			else
			{
				Target	target = parseLHS(lhsTokens);
				executeQuery(ctx, target, rhsTokens);
			}
			return ;
		}
		Target	target = parseLHS(lhsTokens);
		executeAssignment(ctx, history, target, rhsTokens, rawLine);
	}
}
