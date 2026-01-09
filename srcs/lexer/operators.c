/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:41:53 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/09 21:57:19 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

bool	is_operator_char(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '&' || c == ';' || c == '(' || c == ')' || c == '{' || c == '}');
}

t_token	*handle_sigle_operator(const char **input)
{
	if ((*input)[0] == '|')
		return ((*input)++, new_token(PIPE, "|"));
	if ((*input)[0] == '>')
		return ((*input)++, new_token(REDIR_OUT, ">"));
	if ((*input)[0] == '<')
		return ((*input)++, new_token(REDIR_IN, "<"));
	if ((*input)[0] == '&')
		return ((*input)++, new_token(AMPERSAND, "&"));
	if ((*input)[0] == ';')
		return ((*input)++, new_token(SEMICOLON, ";"));
	if ((*input)[0] == '(')
		return ((*input)++, new_token(LPAREN, "("));
	if ((*input)[0] == ')')
		return ((*input)++, new_token(RPAREN, ")"));
	if ((*input)[0] == '{')
		return ((*input)++, new_token(LBRACE, "{"));
	if ((*input)[0] == '}')
		return ((*input)++, new_token(RBRACE, "}"));

	return (NULL);
}

t_token	*handle_double_operator(const char **input)
{
	if ((*input)[0] == '|' && (*input)[1] == '|')
		return ((*input) += 2, new_token(OR, "||"));
	if ((*input)[0] == '&' && (*input)[1] == '&')
		return ((*input) += 2, new_token(AND, "&&"));
	if ((*input)[0] == '>' && (*input)[1] == '>')
		return ((*input += 2, new_token(REDIR_APPEND, ">>")));
	if ((*input)[0] == '<' && (*input)[1] == '<')
		return ((*input += 2, new_token(REDIR_HEREDOC, "<<")));
	if ((*input)[0] == '>' && (*input)[1] == '&')
		return ((*input += 2, new_token(REDIR_FD_OUT, ">&")));
	if ((*input)[0] == '<' && (*input)[1] == '&')
		return ((*input += 2, new_token(REDIR_FD_IN, "<&")));
	if ((*input)[0] == '$' && (*input)[1] == '{')
		return ((*input += 2, new_token(DOLLAR_BRACE, "${")));

	return (NULL);
}
