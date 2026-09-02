#include "Interpreter.hpp"
#include "InterpreterCommandHandler.hpp"
#include "Plotter.hpp"
#include "Settings.hpp"
#include <iostream>

namespace interpreter_cmd
{
	bool	handle( const std::vector<Token>& tokens, Context& ctx, const std::vector<std::string>& history )
	{
		if (tokens.empty())
			return (false);

		const std::string&	cmd = tokens[0].value;

		if (tokens.size() == 1 && cmd == "list")
		{
			if (ctx.empty())
				std::cout << "No Variables.\n";
			else
			{
				for (const auto& pair : ctx)
					std::cout << pair.first << " : " << pair.second << std::endl;
			}
			return (true);
		}
		if (tokens.size() == 1 && cmd == "history")
		{
			if (history.empty())
				std::cout << "History is empty." << std::endl;
			else
			{
				for (std::size_t i = 0; i < history.size(); i++)
					std::cout << i + 1 << ": " << history[i] << std::endl;
			}
			return (true);
		}
		if (tokens.size() == 1 && cmd == "deg")
		{
			Settings::isDegreeMode = true;
			std::cout << "Angle mode switched to: DEGREES" << std::endl;
			return (true);
		}
		if (tokens.size() == 1 && cmd == "rad")
		{
			Settings::isDegreeMode = false;
			std::cout << "Angle mode switched to: RADIANS" << std::endl;
			return (true);
		}
		if (cmd == "clear")
		{
			if (tokens.size() != 2 || tokens[1].type != TokenType::VARIABLE)
			{
				std::cout << "Usage: clear <variable>\n";
				return (true);
			}

			const std::string&	varToDelete = tokens[1].value;
			auto				it = ctx.find(varToDelete);

			if (it != ctx.end())
			{
				ctx.erase(it);
				std::cout << "Variable/Function '" << varToDelete << "' has been deleted.\n";
			}
			else
				std::cout << "Error: '" << varToDelete << "' is not defined.\n";
			return (true);
		}
		if (tokens.size() == 2 && cmd == "plot" && tokens[1].type == TokenType::VARIABLE)
		{
			const std::string&	targetFunc = tokens[1].value;
			auto				it = ctx.find(targetFunc);

			if (it == ctx.end())
			{
				std::cout << "Error: Unkown function '" << targetFunc << "'.\n";
				return (true);
			}
			if (!std::holds_alternative<Polynomial>(it->second))
			{
				std::cout << "Error: '" << targetFunc << "' is not a function/polynomial.\n";
				return (true);
			}
			Plotter		canvas(80, 60);
			Polynomial	f = std::get<Polynomial>(it->second); 

			canvas.drawLine(0, 30, 80, 30);
			canvas.drawLine(40, 0, 40, 60);

			for (float x = -20; x <= 20; x += 0.1)
			{
				double	y = f.eval(Real(x)).getValue();
				int	px = (x + 20) * 2;
				int	py = (y + 30);
				canvas.set(px, py);
			}
			canvas.display();
			return (true);
		}
		if (tokens.size() == 1 && (cmd == "exit" || cmd == "quit"))
		{
			std::cout << "Exiting ComputorV2, Goodbye!\n";
			throw ExitException();
		}
		if (tokens.size() == 1 && cmd == "help")
		{
			std::cout << "=========================================\n"
					  << "          ComputorV2 - Help Menu         \n"
					  << "=========================================\n"
					  << "  list         - List all saved variables and functions\n"
					  << "  history      - Show the command history\n"
					  << "  clear <var>  - Delete a specific variable or function\n"
					  << "  plot <func>  - Plot a function in an ASCII graph\n"
					  << "  deg / rad    - Switch angle mode for trigonometry\n"
					  << "  help         - Show this help message\n"
					  << "  exit / quit  - Exit the program\n"
					  << "-----------------------------------------\n"
					  << "Built-in functions:\n"
					  << "  cos, sin, tan, sqrt, abs, exp, norm, inv\n"
					  << "=========================================" 
					  << std::endl;
			return (true);
		}
		return (false);
	}
}
