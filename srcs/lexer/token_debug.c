/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:20:00 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/09 18:37:45 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

#ifdef DEBUG

# include <unistd.h>
# include <string.h>

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
	if (type == DOLLAR_BRACE)
		return ("DOLLAR_BRACE");
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
	return (COLOR_RESET);
}

void	token_print_one(t_token *token)
{
	const char	*type_name;
	const char	*color;

	if (!token)
		return ;
	color = get_token_color(token->type);
	type_name = get_token_type_name(token->type);
	write(STDOUT_FILENO, color, strlen(color));
	write(STDOUT_FILENO, "[", 1);
	write(STDOUT_FILENO, type_name, strlen(type_name));
	write(STDOUT_FILENO, "]", 1);
	write(STDOUT_FILENO, COLOR_RESET, strlen(COLOR_RESET));
	write(STDOUT_FILENO, " ", 1);
	if (token->value)
	{
		write(STDOUT_FILENO, "[", 1);
		write(STDOUT_FILENO, COLOR_BOLD, strlen(COLOR_BOLD));
		write(STDOUT_FILENO, token->value, strlen(token->value));
		write(STDOUT_FILENO, COLOR_RESET, strlen(COLOR_RESET));
		write(STDOUT_FILENO, "]", 1);
	}
	else
		write(STDOUT_FILENO, "(null)", 6);
	write(STDOUT_FILENO, "\n", 1);
}

static void	put_number(int n)
{
	char	c;

	if (n >= 10)
		put_number(n / 10);
	c = (n % 10) + '0';
	write(STDOUT_FILENO, &c, 1);
}

void	token_print_all(t_token *tokens)
{
	int	i;

	write(STDOUT_FILENO, "\r\n", 2);
	write(STDOUT_FILENO, COLOR_BOLD, strlen(COLOR_BOLD));
	write(STDOUT_FILENO, "=== TOKENS DEBUG ===", 20);
	write(STDOUT_FILENO, COLOR_RESET, strlen(COLOR_RESET));
	write(STDOUT_FILENO, "\n", 1);
	i = 0;
	while (tokens)
	{
		write(STDOUT_FILENO, "\r[", 2);
		put_number(i++);
		write(STDOUT_FILENO, "] -> ", 5);
		token_print_one(tokens);
		tokens = tokens->next;
	}
	write(STDOUT_FILENO, COLOR_BOLD, strlen(COLOR_BOLD));
	write(STDOUT_FILENO, "\r", 1);
	write(STDOUT_FILENO, "====================", 20);
	write(STDOUT_FILENO, COLOR_RESET, strlen(COLOR_RESET));
	write(STDOUT_FILENO, "\n\n", 2);
}

#endif
