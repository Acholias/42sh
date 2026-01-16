/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:03:39 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/16 17:17:34 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	setup_redirections(t_redir *redirs)
{
	int		fd;
	t_redir	*current;

	current = redirs;
	while (current)
	{
		if (current->type== REDIR_IN)
			fd = open(current->file, O_RDONLY);
		else if (current->type == REDIR_OUT)
			fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC | 0644);
		else if (current->type == REDIR_APPEND)
			fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND | 0644);
		else
		{
			current = current->next;
			continue ;
		}
		if (fd < 0)
		{
			perror(current->file);
			return (1);
		}
		dup2(fd, current->fd);
		close(fd);
		current = current->next;
	}
	return (0);
}

void	restore_redirections(int stdin_backup, int stdout_backup)
{
	if (stdin_backup >= 0)
	{
		dup2(stdin_backup, STDIN_FILENO);
		close(stdin_backup);
	}
	if (stdout_backup >= 0)
	{
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdout_backup);
	}
}
