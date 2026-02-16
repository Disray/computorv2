
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

void	Interpreter::executeQuery( const Target& target, const std::vector<Token>& rhsTokens ) const
{
	auto it = _ctx.find(target.name);
	if (it == _ctx.end())
		throw std::runtime_error("Unknown variable or function: " + target.name);

	if (!rhsTokens.empty())
	{
		if (!target.isFunction)
			throw std::runtime_error("Cannot evaluate an expression on a simple variable. Did you mean '==' ?");

		const Polynomial*	poly = std::get_if<Polynomial>(&it->second);
		if (!poly)
			throw std::runtime_error(target.name + " is not a polynomial function.");

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
			auto	itParam = _ctx.find(target.param);
			if (itParam == _ctx.end())
				throw std::runtime_error("Parameter '" + target.param + "' is not defined in context.");

			const Polynomial*	poly = std::get_if<Polynomial>(&it->second);

			if (!poly)
				throw std::runtime_error(target.name + " is not a polynomial function.");
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
		evalCtx[target.param] = Polynomial({0, 1});

	Parser	parser(rhsTokens);
	VarType	result = parser.parse()->eval(evalCtx);

	if (target.isFunction && !std::holds_alternative<Polynomial>(result))
		throw std::runtime_error("Function must evaluate to a Polynomial");

	_ctx[target.name] = result;

	std::cout << target.name;
	if (target.isFunction)
		std::cout << "(" << target.param << ")";
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

	if (isQuery)
	{
		if (rhsTokens.empty())
		{
			Parser	parser(lhsTokens);
			printVarType(parser.parse()->eval(_ctx));
		}
		else
		{
			Target	target = parseLHS(lhsTokens);
			executeQuery(target, rhsTokens);
		}
	}
	else
	{
		Target	target = parseLHS(lhsTokens);
		executeAssignment(target, rhsTokens);
	}
}
