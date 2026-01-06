/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:03:16 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/06 19:37:56 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/term.h"
#include "../../includes/keys.h"
#include "../../includes/display.h"
#include "../../includes/readline.h"

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
	terminal->raw.c_lflag &= ~ECHOCTL;
	terminal->enabled = false;
	terminal->killring = NULL;
	signals_init_interactive();
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
	if (terminal->killring)
	{
		free(terminal->killring);
		terminal->killring = NULL;
	}
	terminal->enabled = false;
	return (0);
}

int	manage_terminal(t_term *terminal)
{
	t_key_result	key;
	t_line			line;

	if (!terminal)
		return (-1);
	buffer_init(&line, 1024);
	signal_set_current_line(&line);
	signal_set_current_term(terminal);
	write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
	while (1)
	{
		if (g_interrupted)
		{
			signal_reset_buffer(&line);
			continue ;
		}
		signal_handle_winch(&line);
		key = get_key();
		if (key.key == KEY_ESC || key.key == KEY_CTRL_D)
			break ;
		if (is_shortcuts_key(key))
			handle_shortcuts(terminal, &line, key);
		else if (is_mouvements_key(key))
			handle_mouvements(&line, key);
		else if (key.key == KEY_BACKSPACE)
			buffer_backspace(&line);
		else if (key.key == KEY_UNKNOWN && key.character)
			buffer_insert(&line, key.character);
		display_refresh_buffer(&line);
	}
	signal_set_current_line(NULL);
	signal_set_current_term(NULL);
	buffer_free(&line);
	return (0);
}
