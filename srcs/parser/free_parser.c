/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:11:08 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/09 19:12:44 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

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
