/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:01:27 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/16 17:10:16 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	execute_and(t_ast_node *node, t_exec_ctx *ctx)
{
	int	left_ret;

	if (!node || !node->left)
		return (1);
	left_ret = executor_run(node->left, ctx);
	if (left_ret == 0 && node->right)
		return (executor_run(node->right, ctx));
	return (left_ret);
}

int	execute_or(t_ast_node *node, t_exec_ctx *ctx)
{
	int	left_ret;

	if (!node || !node->left)
		return (1);
	left_ret = executor_run(node->left, ctx);
	if (left_ret != 0 && node->right)
		return (executor_run(node->right, ctx));
	return (left_ret);
}

int	execute_sequence(t_ast_node *node, t_exec_ctx *ctx)
{
	int	ret;

	if (!node || !node->left)
		return (1);
	executor_run(node->left, ctx);
	if (node->right)
		ret = executor_run(node->right, ctx);
	else
		ret = ctx->last_exit_code;
	return (ret);
}

int	execute_background(t_ast_node *node, t_exec_ctx *ctx)
{
	if (!node || !node->left)
		return (1);
	return (executor_run(node->left, ctx));
}

int	execute_subshell(t_ast_node *node, t_exec_ctx *ctx)
{
	if (!node || !node->left)
		return (1);
	return (executor_run(node->child, ctx));
}
