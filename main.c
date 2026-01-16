/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:33:34 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/16 18:43:33 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int	main(int argc, char **argv, char **env)
{
	t_term		terminal;
	t_env		*new_env;
	t_exec_ctx	*exec_ctx;

	(void)argc;
	(void)argv;
	new_env = init_env(env);
	if (terminal_init(&terminal) == -1)
		return (-1);
	if (terminal_enable(&terminal) == -1)
	{
		terminal_disable(&terminal);
		return (-1);
	}
	exec_ctx = executor_init(&new_env);
	if (!exec_ctx)
	{
		terminal_disable(&terminal);
		free_env(&new_env);
		return (-1);
	}
	readline_loop(&terminal, exec_ctx);
	free_executor(exec_ctx);
	terminal_disable(&terminal);
	display_newline();
	free_env(&new_env);
	close(6); // WSL PROTECTION
	return (0);
}
