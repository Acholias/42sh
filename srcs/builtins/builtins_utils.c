/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:08:13 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/16 15:14:34 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

bool	is_builtin(const char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	if (ft_strcmp(cmd, "env") == 0)
		return (true);
	if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd, "export") == 0)
		return (true);
	if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	return (false);
}

int	execute_builtins(char **argv, t_env **env)
{
	if (!argv || !argv[0])
		return (-1);
	if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(argv));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(argv[0], "exit") == 0)
		return (ft_exit(argv, 0));
	if (ft_strcmp(argv[0], "env") == 0)
		return (ft_env(*env));
	if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(argv, env));
	if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(argv, env));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(argv, env));
	return (1);
}
