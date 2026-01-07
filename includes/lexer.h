/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:07:10 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/07 17:21:12 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

typedef enum	e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	AND,
	OR,
	SEMICOLON,
	AMPERSAND,
	LPAREN,
	RPAREN,
	TOKEN_EOF,
	REDIR_FD_IN,
	REDIR_FD_OUT,
	LBRACE,
	RBRACE,
	DQUOTE,
	SQUOTE,
	BACKSLASH,
	DOLLAR,
	DOLLAR_BRACE,
	TILDE
}	t_token_type;

typedef struct	s_token
{
	t_token_type	type;
	char			*value;
	struct	s_token	*next;
}	t_token;

#endif
