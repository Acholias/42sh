/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:59:07 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/06 23:46:35 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include <sys/ioctl.h>

void	display_clear_line(void)
{
	write(STDOUT_FILENO, "\033[2K\r", 5);
}

void	display_clear_screen(void)
{
	write(STDOUT_FILENO, "\033[2J\033[H", 7);
}

void	display_cursor_left(int n)
{
	char	seq[16];

	if (n <= 0)
		return ;
	snprintf(seq, sizeof(seq), "\033[%dD", n);
	write(STDOUT_FILENO, seq, ft_strlen(seq));
}

void	display_cursor_right(int n)
{
	char	seq[16];

	if (n <= 0)
		return ;
	snprintf(seq, sizeof(seq), "\033[%dC", n);
	write(STDOUT_FILENO, seq, ft_strlen(seq));
}

void	display_move_cursor_to(int position)
{
	char	seq[16];
	if (position < 0)
		return ;
	snprintf(seq, sizeof(seq), "\033[%dG", position + 1);
	write(STDOUT_FILENO, seq, ft_strlen(seq));
}

void	display_save_cursor(void)
{
	write(STDOUT_FILENO, "\033[s", 3);
}

void	display_restore_cursor(void)
{
	write(STDOUT_FILENO, "\033[u", 3);
}

int	display_get_terminal_width(void)
{
	struct	winsize	ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
		return (80);
	return (ws.ws_col);
}

static int	display_get_prompt_length(void)
{
	int		len;
	int		index;
	bool	in_escape;

	len = 0;
	index = 0;
	in_escape = false;
	while (PROMPT[index])
	{
		if (PROMPT[index] == '\033')
			in_escape = true;
		else if (in_escape && PROMPT[index] == 'm')
			in_escape = false;
		else if (!in_escape)
			len++;
		index++;
	}
	return (len);
}

void	display_refresh_buffer(const t_line *line)
{
	int	prompt_len;

	display_clear_line();
	write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
	write(STDOUT_FILENO, line->buffer, line->len);
	prompt_len = display_get_prompt_length();
	display_move_cursor_to(prompt_len + line->pos);
}

void	display_refresh_with_clear(const t_line *line)
{
	display_clear_screen();
	display_refresh_buffer(line);
}

void	display_newline(void)
{
	write(STDOUT_FILENO, "\n", 1);
}

void	display_prompt(void)
{
	write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}

void	display_bell(void)
{
	write(STDOUT_FILENO, "\a", 1);
}
