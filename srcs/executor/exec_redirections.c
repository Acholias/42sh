/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:03:39 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/16 18:32:38 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	setup_redirections(t_redir *redirs, int *stdin_backup, int *stdout_backup)
{
	int		fd;
	t_redir	*current;

	*stdin_backup = -1;
	*stdout_backup = -1;
	current = redirs;
	while (current)
	{
		if (current->type == REDIR_IN)
			fd = open(current->file, O_RDONLY);
		else if (current->type == REDIR_OUT)
			fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (current->type == REDIR_APPEND)
			fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
		{
			current = current->next;
			continue ;
		}
		if (fd < 0)
		{
			perror(current->file);
			restore_redirections(*stdin_backup, *stdout_backup);
			return (1);
		}
		if (current->fd == STDIN_FILENO && *stdin_backup == -1)
			*stdin_backup = dup(STDIN_FILENO);
		else if (current->fd == STDOUT_FILENO && *stdout_backup == -1)
			*stdout_backup = dup(STDOUT_FILENO);
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
