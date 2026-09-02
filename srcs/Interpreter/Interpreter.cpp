#include "Interpreter.hpp"
#include "InterpreterCommandHandler.hpp"
#include "InterpreterEvaluator.hpp"
#include "TokenPreprocessor.hpp"

Interpreter::Interpreter( Context& ctx ) : _ctx(ctx)
{
	_ctx["pi"] = Real(maths::pi);
	_ctx["e"] = Real(maths::e);
	_ctx["sqrt2"] = Real(maths::sqrt2);
	_ctx["i"] = Complex(0, 1);
}

Interpreter::~Interpreter() {}

void	Interpreter::processLine( std::vector<Token>& tokens, const std::string& rawLine )
{
	if (tokens.empty())
		return ;

	bool	isQuery = false;

	if (tokens.back().type == TokenType::QUERY)
	{
		isQuery = true;
		tokens.pop_back();
		if (tokens.empty())
			return ;
	}
	if (interpreter_cmd::handle(tokens, _ctx, _history))
	{
		_history.push_back(rawLine);
		return ;
	}
	token_preproc::normalize(tokens);
	interpreter_eval::execute(_ctx, _history, tokens, isQuery, rawLine);
}
