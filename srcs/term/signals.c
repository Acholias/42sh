/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:49:42 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/06 12:19:47 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/readline.h"

volatile sig_atomic_t g_interrupted = 0;

void	handle_signal(int signal)
{
	(void)signal;
	g_interrupted = 1;
}

void	signal_reset_buffer(t_line *line)
{
	write(STDOUT_FILENO, "^C", 2);
	g_interrupted = 0;
	line->pos = 0;
	line->len = 0;
	if (line->buffer)
		line->buffer[0] = '\0';
	write(STDOUT_FILENO, "\n\r", 2);
	write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}
