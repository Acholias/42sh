/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:59:07 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/05 23:47:03 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/display.h"
#include "../../includes/readline.h"

void	display_clear_line(void)
{
	write(STDOUT_FILENO, "\033[2K\r", 5);
}

void	display_cursor_left(int n)
{
	char	seq[16];

	if (n <= 0)
		return ;
	snprintf(seq, sizeof(seq), "\033[%dD", n);
	write(STDOUT_FILENO, seq, strlen(seq));
}

void	display_cursor_right(int n)
{
	char	seq[16];

	if (n <= 0)
		return ;
	snprintf(seq, sizeof(seq), "\033[%dC", n);
	write(STDOUT_FILENO, seq, strlen(seq));
}

void	display_refresh_buffer(const t_line *line)
{
	display_clear_line();
	write(STDOUT_FILENO, "$> ", 3);
	write(STDOUT_FILENO, line->buffer, line->len);
	display_cursor_left(line->len - line->pos);
}
