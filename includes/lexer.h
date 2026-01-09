/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:07:10 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/08 18:26:58 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>

# define MALLOC_FAILED NULL

// Forward declaration pour ast_print_debug
typedef struct s_ast_node	t_ast_node;

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
	DOLLAR_BRACE,
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
t_token	*lexer_tokenizer(const char *input);

// quotes.c
bool	check_quotes_closed(const char *input);
char	*extract_quoted_word(const char **input);


// debug
void	token_print_all(t_token *token);
void	ast_print_debug(t_ast_node *ast);

#endif
