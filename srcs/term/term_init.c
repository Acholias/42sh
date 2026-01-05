/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:03:16 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/05 18:37:14 by lumugot          ###   ########.fr       */
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
