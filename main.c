/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:33:34 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/12 10:24:47 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/display.h"
#include "includes/term.h"
#include "includes/env.h"

// void	print_env(t_env *env)
// {
// 	while (env)
// 	{
// 		write(STDOUT_FILENO, env->name, strlen(env->name));
// 		write(STDOUT_FILENO, "=", 1);
// 		write(STDOUT_FILENO, env->value, strlen(env->value));
// 		write(STDOUT_FILENO, "\n", 1);
// 		env = env->next;
// 	}
// }

int	main(int argc, char **argv, char **env)
{
	t_term	terminal;
	t_env	*new_env;

	(void)argc;
	(void)argv;
	new_env = init_env(env);
	// print_env(new_env);
	if (terminal_init(&terminal) == -1)
		return (-1);
	if (terminal_enable(&terminal) == -1)
	{
		terminal_disable(&terminal);
		return (-1);
	}
	readline_loop(&terminal);
	terminal_disable(&terminal);
	display_newline();
	close(6); // WSL PROTECTION
	free_env(&new_env);
	return (0);
}
