/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:17:19 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/16 18:07:55 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static	int	execute_pipe_left(t_ast_node *left, int *pipefd, t_exec_ctx *ctx)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exit(executor_run(left, ctx));
	}
	return (pid);
}

static	int	execute_pipe_right(t_ast_node *right, int *pipefd, t_exec_ctx *ctx)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDOUT_FILENO);
		close(pipefd[0]);
		exit(executor_run(right, ctx));
	}
	return (pid);
}

int	execute_pipe(t_ast_node *node, t_exec_ctx *ctx)
{
	int		pipefd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;
	int		ret;

	ret = 0;
	if (!node || !node->left || !node->right)
		return (1);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid_left = execute_pipe_left(node->left, pipefd, ctx);
	pid_right = execute_pipe_right(node->right, pipefd, ctx);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	return (ret);
}
