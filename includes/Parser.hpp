/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:02:56 by rrichard          #+#    #+#             */
/*   Updated: 2026/01/14 12:54:58 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		NodePtr						parse_primary();

		const Token&				peek() const;
		const Token&				advance();
		const Token&				consume( TokenType );
		bool						match( TokenType );
		bool						match_op( OpKind );
	
	public:
		explicit Parser( const std::vector<Token>& t ) : tokens(t), pos(0) {}
		
		NodePtr	parse();
};