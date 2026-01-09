/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:26:11 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/09 18:45:37 by lumugot          ###   ########.fr       */
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

#endif

