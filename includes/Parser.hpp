#include "Nodes.hpp"

class Parser
{
	private:
		const std::vector<Token>&	tokens;
		size_t						pos;
		
		NodePtr						parse_matrix();
		NodePtr						parse_expression();
		NodePtr						parse_term();
		NodePtr						parse_factor();
		NodePtr						parse_power();
		NodePtr						parse_primary();

		const Token&				peek() const;
		const Token&				advance();
		const Token&				consume( TokenType );
		bool						match( TokenType );
		bool						match_op( OpKind );

	public:
		explicit Parser( const std::vector<Token>& t ) : tokens(t), pos(0) {}

		NodePtr						parse();
		static bool					isBuiltinFunction( const std::string& );
};
