/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:59:07 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/05 20:27:23 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/term.h"

void	clear_line(void)
{
	write(STDOUT_FILENO, "\033[2K\r", 5);
}

void	cursor_left(int n)
{
	char	seq[16];

	if (n <= 0)
		return ;
	snprintf(seq, sizeof(seq), "\033[%dD", n);
	write(STDOUT_FILENO, seq, strlen(seq));
}

void	cursor_right(int n)
{
	char	seq[16];

	if (n <= 0)
		return ;
	snprintf(seq, sizeof(seq), "\033[%dC", n);
	write(STDOUT_FILENO, seq, strlen(seq));
}

void	display_buffer(const char *buffer, int cursor_pos)
{
	int	len;

	len = strlen(buffer);
	clear_line();
	write(STDOUT_FILENO, buffer, len);
	cursor_left(len - cursor_pos);
}
