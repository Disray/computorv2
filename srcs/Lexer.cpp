#include "Lexer.hpp"
#include <regex>
#include <cctype>

Lexer::Lexer() {}
Lexer::~Lexer() {}

Token	Lexer::createSymbolToken( const std::string& str ) const
{
	static const std::map<std::string, TokenDef>	symbolMap = {
		{"=",  {TokenType::EQUAL,				 OpKind::NONE}},
		{"[",  {TokenType::BRACKET_MATRIX_OPEN,	 OpKind::NONE}},
		{"]",  {TokenType::BRACKET_MATRIX_CLOSE, OpKind::NONE}},
		{"(",  {TokenType::BRACKET_OPEN,		 OpKind::NONE}},
		{")",  {TokenType::BRACKET_CLOSE,		 OpKind::NONE}},
		{",",  {TokenType::COMMA,				 OpKind::NONE}},
		{";",  {TokenType::SEMICOLON,			 OpKind::NONE}},
		{"?",  {TokenType::QUERY,				 OpKind::NONE}},
		{"+",  {TokenType::OPERATOR,			 OpKind::ADD}},
		{"-",  {TokenType::OPERATOR,			 OpKind::SUB}},
		{"**", {TokenType::OPERATOR,			 OpKind::MUL_MAT}},
		{"*",  {TokenType::OPERATOR,			 OpKind::MUL}},
		{"/",  {TokenType::OPERATOR,			 OpKind::DIV}},
		{"%",  {TokenType::OPERATOR,			 OpKind::MOD}},
		{"^",  {TokenType::OPERATOR,			 OpKind::POW}},
	};

	auto	it = symbolMap.find(str);
	if (it != symbolMap.end())
		return (Token(str, it->second.first, Arity::CONSTANT, it->second.second));
	return (Token(str, TokenType::UNKOWN, Arity::CONSTANT, OpKind::NONE));
}

std::vector<Token>	Lexer::tokenize( const std::string& input ) const
{
	const std::regex 	pattern("([0-9]+(\\.[0-9]+)?)|([a-zA-Z][a-zA-Z0-9_]*)|(\\*\\*|[\\+\\-\\*\\/%\\^\\(\\)=])|([\\[\\]\\,\\;])|(\\?)");
	auto				words_begin = std::sregex_iterator(input.begin(), input.end(), pattern);
	auto				words_end	= std::sregex_iterator();
	std::vector<Token>	tokens;

	for (std::sregex_iterator i = words_begin; i != words_end; i++)
	{
		std::string	match_str = i->str();

		if (isdigit(match_str[0]))
			tokens.emplace_back(match_str, TokenType::NUMBER, Arity::CONSTANT, OpKind::NONE);
		else if (isalpha(match_str[0]))
		{
			for (auto& c : match_str)
				c = std::tolower(static_cast<unsigned char>(c));
			TokenType	type = (match_str == "i") ? TokenType::IMAGINARY : TokenType::VARIABLE;

			tokens.emplace_back(match_str, type, Arity::CONSTANT, OpKind::NONE);
		}
		else
			tokens.push_back(createSymbolToken(match_str));
	}
	return (tokens);
}
