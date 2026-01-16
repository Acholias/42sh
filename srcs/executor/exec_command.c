/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:57:31 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/16 16:14:41 by lumugot          ###   ########.fr       */
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
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (ast->redirs && setup_redirections(ast->redirs) != 0)
	{
		restore_redirections(stdin_backup, stdout_backup);
		return (1);
	}
	if (is_builtin(ast->cmd->argv[0]))
		ret = execute_builtins(ast->cmd->argv, ctx->env);
	else
		ret = execute_external(ast->cmd, ctx);
	restore_redirections(stdin_backup, stdout_backup);
	return (ret);
}