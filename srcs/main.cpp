
#include <string>
#include <map>
#include <variant>
#include <regex>
#include "computor.hpp"
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
		std::cout << "> ";
		if (!std::getline(std::cin, line))
		{
			std::cout << std::endl;
			break;
		}
		if (line.empty())
			continue;
		try
		{
			auto	tokens = lexer.tokenize(line);
			interpret.processLine(tokens);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	return (0);
}
