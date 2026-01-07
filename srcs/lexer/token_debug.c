/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:20:00 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/07 18:20:00 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

#ifdef DEBUG

# include <stdio.h>

# define COLOR_RESET   "\033[0m"
# define COLOR_BOLD    "\033[1m"
# define COLOR_CYAN    "\033[36m"
# define COLOR_GREEN   "\033[32m"
# define COLOR_YELLOW  "\033[33m"
# define COLOR_MAGENTA "\033[35m"
# define COLOR_RED     "\033[31m"

static const char	*get_token_type_name(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIR_IN)
		return ("REDIR_IN");
	if (type == REDIR_OUT)
		return ("REDIR_OUT");
	if (type == REDIR_APPEND)
		return ("REDIR_APPEND");
	if (type == REDIR_HEREDOC)
		return ("REDIR_HEREDOC");
	if (type == AND)
		return ("AND");
	if (type == OR)
		return ("OR");
	if (type == SEMICOLON)
		return ("SEMICOLON");
	if (type == AMPERSAND)
		return ("AMPERSAND");
	if (type == LPAREN)
		return ("LPAREN");
	if (type == RPAREN)
		return ("RPAREN");
	if (type == TOKEN_EOF)
		return ("EOF");
	if (type == REDIR_FD_IN)
		return ("REDIR_FD_IN");
	if (type == REDIR_FD_OUT)
		return ("REDIR_FD_OUT");
	if (type == LBRACE)
		return ("LBRACE");
	if (type == RBRACE)
		return ("RBRACE");
	if (type == DQUOTE)
		return ("DQUOTE");
	if (type == SQUOTE)
		return ("SQUOTE");
	if (type == BACKSLASH)
		return ("BACKSLASH");
	if (type == DOLLAR)
		return ("DOLLAR");
	if (type == DOLLAR_BRACE)
		return ("DOLLAR_BRACE");
	if (type == TILDE)
		return ("TILDE");
	return ("UNKNOWN");
}

static const char	*get_token_color(t_token_type type)
{
	if (type == WORD)
		return (COLOR_GREEN);
	if (type == PIPE || type == AND || type == OR || type == SEMICOLON)
		return (COLOR_YELLOW);
	if (type >= REDIR_IN && type <= REDIR_FD_OUT)
		return (COLOR_CYAN);
	if (type == LPAREN || type == RPAREN || type == LBRACE || type == RBRACE)
		return (COLOR_MAGENTA);
	if (type == DQUOTE || type == SQUOTE || type == BACKSLASH)
		return (COLOR_RED);
	return (COLOR_RESET);
}

void	token_print_one(t_token *token)
{
	if (!token)
		return ;
	printf("%s[%-16s]%s ", get_token_color(token->type),
		get_token_type_name(token->type), COLOR_RESET);
	if (token->value)
		printf("'%s%s%s'", COLOR_BOLD, token->value, COLOR_RESET);
	else
		printf("(null)");
	printf("\n");
}

void	token_print_all(t_token *tokens)
{
	int	i;

	printf("\n%s=== TOKENS DEBUG ===%s\n", COLOR_BOLD, COLOR_RESET);
	i = 0;
	while (tokens)
	{
		printf("%s[%d]%s ", COLOR_CYAN, i++, COLOR_RESET);
		token_print_one(tokens);
		tokens = tokens->next;
	}
	printf("%s====================%s\n\n", COLOR_BOLD, COLOR_RESET);
}

#endif
