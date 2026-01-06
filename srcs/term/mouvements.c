/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:05:40 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/06 00:41:46 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/readline.h"

bool	is_mouvements_key(t_key_result key)
{
	if (key.key == KEY_CTRL_A || key.key == KEY_CTRL_E)
		return (true);
	if (key.key == KEY_HOME || key.key == KEY_END)
		return (true);
	if (key.key == KEY_ARROW_LEFT || key.key == KEY_ARROW_RIGHT)
		return (true);
	return (false);
}

void	handle_mouvements(t_line *line, t_key_result key)
{
	if (!line)
		return ;

	if (key.key == KEY_CTRL_A || key.key == KEY_HOME)
		cursor_home(line);
	else if (key.key == KEY_CTRL_E || key.key == KEY_END)
		cursor_end(line);
	else if (key.key == KEY_ARROW_LEFT && line->pos > 0)
		cursor_left(line);
	else if (key.key == KEY_ARROW_RIGHT && line->pos < line->len)
		cursor_right(line);
}
