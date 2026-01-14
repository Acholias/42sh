/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:11:08 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/09 19:30:10 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	simple_cmd_free(t_simple_cmd *cmd)
{
	int	index;
	
	if (!cmd)
		return ;
	if (cmd->argv)
	{
		index = 0;
		while (index < cmd->argc)
		{
			free(cmd->argv[index]);
			index++;
		}
		free(cmd->argv);
	}
	free(cmd);
}

void	redir_free(t_redir *redirs)
{
	t_redir	*next;

	while (redirs)
	{
		next = redirs->next;
		free(redirs->file);
		free(redirs->heredoc);
		free(redirs);
		redirs = next;
	}
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->cmd)
		simple_cmd_free(node->cmd);
	if (node->redirs)
		redir_free(node->redirs);
	if (node->left)
		free_ast(node->left);
	if (node->right)
		free_ast(node->right);
	if (node->child)
		free_ast(node->child);
	free(node);
}
