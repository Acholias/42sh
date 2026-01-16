/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:58:34 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/16 18:51:53 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "env.h"
# include "parser.h"
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_exec_ctx
{
	t_env	**env;
	int		last_exit_code;
	int		stdin_backup;
	int		stdout_backup;
}	t_exec_ctx;

// executor.c
t_exec_ctx	*executor_init(t_env **env);
void		free_executor(t_exec_ctx *ctx);
int			executor_run(t_ast_node *ast, t_exec_ctx *ctx);

// exec_command.c
int			execute_command(t_ast_node *ast, t_exec_ctx *ctx);

// exec_redirextions.c
int			setup_redirections(t_redir *redirs, int *stdin_backup, int *stdout_backup);
void		restore_redirections(int stdin_backup, int stdout_backup);

// exec_pipe.c
int			execute_pipe(t_ast_node *node, t_exec_ctx *ctx);

// exec_operators.c
int			execute_and(t_ast_node *node, t_exec_ctx *ctx);
int			execute_or(t_ast_node *node, t_exec_ctx *ctx);
int			execute_sequence(t_ast_node *node, t_exec_ctx *ctx);
int			execute_background(t_ast_node *node, t_exec_ctx *ctx);
int			execute_subshell(t_ast_node *node, t_exec_ctx *ctx);

// external.c
char		**env_to_array(t_env *env);
char		*find_command_path(const char *cmd, t_env *env);
int			execute_external(t_simple_cmd *cmd, t_exec_ctx *ctx);

#endif
