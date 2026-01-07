/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:07:10 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/07 18:29:59 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

# define MALLOC_FAILED NULL

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

// token_utils.c
t_token	*new_token(t_token_type type, const char *value);
void	token_add_back(t_token **head, t_token *new_token);
void	token_free(t_token *tokens);

// operators.c
bool	is_operator_char(char c);
t_token	*handle_sigle_operator(const char **input);
t_token	*handle_double_operator(const char **input);

// tokenizer.c


#endif
