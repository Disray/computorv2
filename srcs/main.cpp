#include <string>
#include <map>
#include <variant>
#include <regex>
#include <readline/readline.h>
#include <readline/history.h>
#include <cstdlib>
#include "RuntimeTypes.hpp"
#include "Interpreter.hpp"
#include "Lexer.hpp"

int	main( void )
{
	std::string	line;
	Context		ctx;
	Interpreter	interpret(ctx);
	Lexer		lexer;

	while (true)
	{
		char*	input = readline("> ");

		if (!input)
		{
			std::cout << std::endl;
			break;
		}
		std::string	line(input);

		if (!line.empty())
			add_history(input);
		free(input);
		if (line.empty())
			continue ;
		try
		{
			auto	tokens = lexer.tokenize(line);
			interpret.processLine(tokens, line);
		}
		catch (const ExitException& e)
		{
			break ;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	return (0);
}
