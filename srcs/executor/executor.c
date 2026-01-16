/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:24:03 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/16 15:56:27 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include <unistd.h>

t_exec_ctx	*executor_init(t_env **env)
{
	t_exec_ctx	*ctx;

	ctx = malloc(sizeof(t_exec_ctx));
	if (!ctx)
		return (MALLOC_FAILED);
	ctx->env = env;
	ctx->last_exit_code = 0;
	ctx->stdin_backup = dup(STDIN_FILENO);
	ctx->stdout_backup = dup(STDOUT_FILENO);
	return (ctx);
}

void	executor_free(t_exec_ctx *ctx)
{
	if (!ctx)
		return ;
	if (ctx->stdin_backup >= 0)
		close(ctx->stdin_backup);
	if (ctx->stdout_backup >= 0)
		close(ctx->stdout_backup);
	free(ctx);
}

int	executor_run(t_ast_node *ast, t_exec_ctx *ctx)
{
	int	ret;

	if (!ast || !ctx)
		return (1);
	if (ast->type == NODE_COMMAND)
		ret = execute_command(ast, ctx);
	else if (ast->type == NODE_PIPE)
		ret = execute_pipe(ast, ctx);
	else if (ast->type == NODE_AND)
		ret = execute_and(ast, ctx);
	else if (ast->type == NODE_OR)
		ret = execute_or(ast, ctx);
	else if (ast->type == NODE_SEQUENCE)
		ret = execute_sequence(ast, ctx);
	else if (ast->type == NODE_BACKGROUND)
		ret = execute_background(ast, ctx);
	else if (ast->type == NODE_SUBSHELL)
		ret = execute_subshell(ast, ctx);
	else
		ret = 1;
	ctx->last_exit_code = ret;
	return (ret);
}
