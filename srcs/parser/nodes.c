/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:14:33 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/09 19:25:30 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

t_ast_node	*new_command_node(t_simple_cmd *cmd, t_redir *redirs)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (MALLOC_FAILED);
	node->type = NODE_COMMAND;
	node->cmd = cmd;
	node->redirs = redirs;
	node->left = NULL;
	node->right = NULL;
	node->child = NULL;
	return (node);
}

t_ast_node	*new_binary_node(t_node_type type, t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (MALLOC_FAILED);
	node->type = type;
	node->cmd = NULL;
	node->redirs = NULL;
	node->left = left;
	node->right = right;
	node->child = NULL;
	return (node);
}

t_ast_node	*new_unary_node(t_node_type type, t_ast_node *child)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (MALLOC_FAILED);
	node->type = type;
	node->cmd = NULL;
	node->redirs = NULL;
	node->left = NULL;
	node->right = NULL;
	node->child = child;
	return (node);
}
