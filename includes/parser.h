/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:26:11 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/09 21:27:10 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef enum	e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIR,
	NODE_AND,
	NODE_OR,
	NODE_SEQUENCE,
	NODE_BACKGROUND,
	NODE_SUBSHELL,
	NODE_GROUP
}	t_node_type;

typedef struct	s_simple_cmd
{
	char	**argv;
	int		argc;
}	t_simple_cmd;

typedef struct	s_redir
{
	t_token_type	type;
	int				fd;
	char			*file;
	char			*heredoc;
	struct s_redir	*next;
}	t_redir;

typedef struct	s_ast_node
{
	t_node_type			type;
	t_simple_cmd		*cmd;
	t_redir				*redirs;
	struct	s_ast_node	*left;
	struct	s_ast_node	*right;
	struct	s_ast_node	*child; // Pour SUBSHELL OU NODE_GROUP, peut etre pas utile
}	t_ast_node;

// parser_utils.c
bool		is_redir(t_token_type type);
t_token		*get_current_token(t_token *token);
t_token		*advance_next_token(t_token **token);
bool		match_token(t_token **token, t_token_type type);

// free_parser.c
void		simple_cmd_free(t_simple_cmd *cmd);
void		redir_free(t_redir *redirs);
void		free_ast(t_ast_node *node);

// nodes.c
t_ast_node	*new_command_node(t_simple_cmd *cmd, t_redir *redirs);
t_ast_node	*new_binary_node(t_node_type type, t_ast_node *left, t_ast_node *right);
t_ast_node	*new_unary_node(t_node_type type, t_ast_node *child);

// redirections.c
t_redir		*new_redir(t_token_type, int fd, char *file);
void		redir_add_back(t_redir **head, t_redir *new_redir);
t_ast_node	*parse_redirs(t_token **token, t_ast_node *cmd);

// grammar.c
t_ast_node	*parse_complete_command(t_token **token);

// parser.c
t_ast_node	*parser_build_ast(t_token *token);

#endif

