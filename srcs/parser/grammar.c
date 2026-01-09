/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:00:12 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/09 19:19:53 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_ast_node	*parse_simple_command(t_token **token)
{
	t_simple_cmd	*cmd;
	t_token			*current;
	int				index;

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
