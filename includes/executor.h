/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:58:34 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/16 15:23:51 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "env.h"
# include "parser.h"
# include <sys/wait.h>

typedef struct s_exec_ctx
{
	char	**env;
	int		last_exit_code;
	int		stdin_backup;
	int		stdout_backup;
}	t_exec_ctx;

// executor.c
t_exec_ctx	*executor_init(t_env **env);
void		free_executor(t_exec_ctx *ctx);
int			executor_run(t_ast_node *ast, t_exec_ctx *ctx);

#endif
