/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:03:16 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/05 20:35:02 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/term.h"

int	terminal_init(t_term *terminal)
{
	if (!terminal)
		return (-1);
	memset(terminal, 0, sizeof(t_term));
	if (tcgetattr(STDIN_FILENO, &terminal->orig) == -1)
		return (-1);
	terminal->raw = terminal->orig;
	cfmakeraw(&terminal->raw);
	terminal->raw.c_lflag |= ISIG;
	terminal->enabled = false;
	return (0);
}

int	terminal_enable(t_term *terminal)
{
	if (!terminal || terminal->enabled)
		return (0);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal->raw) == -1)
		return (-1);
	terminal->enabled = true;
	return (0);
}

int	terminal_disable(t_term *terminal)
{
	if (!terminal || !terminal->enabled)
		return (0);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal->orig) == -1)
		return (-1);
	terminal->enabled = false;
	return (0);
}

int	manage_terminal(t_term *terminal)
{
	t_key_result	key;
	char			buffer[1024] = {0};
	int				pos;
	int				len;

	(void)terminal;
	pos = 0;
	len = 0;
	while (1)
	{
		key = get_key();
		if (key.key == KEY_ESC || key.key == KEY_CTRL_D)
			break;
		
		if (key.key == KEY_UNKNOWN && key.character)
		{
			memmove(&buffer[pos + 1], &buffer[pos], len - pos + 1);
			buffer[pos] = key.character;
			pos++;
			len++;
			buffer[len] = '\0';
		}
		else if (key.key == KEY_BACKSPACE && pos > 0)
		{
			pos--;
			len--;
			memmove(&buffer[pos], &buffer[pos + 1], len - pos + 1);
		}
		else if (key.key == KEY_CTRL_A)
			pos = 0;
		else if (key.key == KEY_CTRL_E)
			pos = len;

		display_buffer(buffer, pos);

	}
	return (0);
}
