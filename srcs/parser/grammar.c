/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:00:12 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/09 21:28:49 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_ast_node	*parse_simple_command(t_token **token)
{
	t_simple_cmd	*cmd;
	t_token			*current;

	cmd = malloc(sizeof(t_simple_cmd));
	if (!cmd)
		return (MALLOC_FAILED);
	cmd->argc = 0;
	cmd->argv = malloc(sizeof(char *) * 256);
	if (!cmd->argv)
	{
		free(cmd);
		return (MALLOC_FAILED);
	}
	while (*token && (*token)->type == WORD)
	{
		current = advance_next_token(token);
		cmd->argv[cmd->argc] = strdup(current->value);
		cmd->argc++;
	}
	cmd->argv[cmd->argc] = NULL;
	if (cmd->argc == 0)
	{
		simple_cmd_free(cmd);
		return (NULL);
	}
	return (new_command_node(cmd, NULL));
}

t_ast_node	*parse_command(t_token **token)
{
	t_ast_node	*node;

	if (!*token)
		return (NULL);
	if ((*token)->type == LPAREN)
	{
		advance_next_token(token);
		node = parse_complete_command(token);
		if (!match_token(token, RPAREN))
		{
			free_ast(node);
			return (NULL);
		}
		return (new_unary_node(NODE_SUBSHELL, node));
	}
	node = parse_simple_command(token);
	if (!node)
		return (NULL);
	return (parse_redirs(token, node));
}

t_ast_node	*parse_pipeline(t_token **token)
{
	t_ast_node	*left;
	t_ast_node	*right;

	left = parse_command(token);
	if (!left)
		return (NULL);
	while (*token && (*token)->type == PIPE)
	{
		advance_next_token(token);
		right = parse_command(token);
		if (!right)
		{
			free_ast(left);
			return (NULL);
		}
		left = new_binary_node(NODE_PIPE, left, right);
	}
	return (left);
}

t_ast_node	*parse_and_or(t_token **token)
{
	t_ast_node		*left;
	t_ast_node		*right;
	t_node_type		type;

	left = parse_pipeline(token);
	if (!left)
		return (NULL);
	while (*token && ((*token)->type == AND || (*token)->type == OR))
	{
		if ((*token)->type == AND)
			type = NODE_AND;
		else
			type = NODE_OR;
		advance_next_token(token);
		right = parse_pipeline(token);
		if (!right)
		{
			free_ast(left);
			return (NULL);
		}
		left = new_binary_node(type, left, right);
	}
	return (left);
}

t_ast_node	*parse_list(t_token **token)
{
	t_ast_node		*left;
	t_ast_node		*right;
	t_node_type		type;

	left = parse_and_or(token);
	if (!left)
		return (NULL);
	while (*token && ((*token)->type == SEMICOLON || (*token)->type == AMPERSAND))
	{
		if ((*token)->type == SEMICOLON)
			type = NODE_SEQUENCE;
		else
			type = NODE_BACKGROUND;
		advance_next_token(token);
		if (!*token)
			return (left);
		right = parse_and_or(token);
		if (!right)
		{
			free_ast(left);
			return (NULL);
		}
		left = new_binary_node(type, left, right);
	}
	return (left);
}

t_ast_node	*parse_complete_command(t_token **token)
{
	return (parse_list(token));
}
