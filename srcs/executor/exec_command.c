/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:57:31 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/16 18:33:53 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	execute_command(t_ast_node *ast, t_exec_ctx *ctx)
{
	int	ret;
	int	stdin_backup;
	int	stdout_backup;

	if (!ast || !ast->cmd || !ast->cmd->argv[0])
		return (1);
	
	stdin_backup = -1;
	stdout_backup = -1;
	
	if (ast->redirs && setup_redirections(ast->redirs, &stdin_backup, &stdout_backup) != 0)
		return (1);
	
	if (is_builtin(ast->cmd->argv[0]))
	{
		ret = execute_builtins(ast->cmd->argv, ctx->env);
		fflush(stdout);
	}
	else
	{
		if (!ast->redirs)
			write(STDOUT_FILENO, "\r", 1);
		ret = execute_external(ast->cmd, ctx);
	}
	restore_redirections(stdin_backup, stdout_backup);
	return (ret);
}
