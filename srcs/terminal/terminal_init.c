/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:49:15 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/07 16:22:39 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include <bits/posix_opt.h>

int	terminal_init(t_term *terminal)
{
	if (!terminal)
		return (-1);
	ft_memset(terminal, 0, sizeof(t_term));
	if (tcgetattr(STDIN_FILENO, &terminal->orig) == -1)
		return (-1);
	terminal->raw = terminal->orig;
	cfmakeraw(&terminal->raw);
	terminal->raw.c_lflag |= ISIG;
	terminal->raw.c_lflag &= ~ECHOCTL;
	terminal->raw.c_cc[VQUIT] = _POSIX_VDISABLE;
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
