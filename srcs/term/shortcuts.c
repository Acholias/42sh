/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcuts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 23:53:49 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/06 00:49:36 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/readline.h"
#include "../../includes/keys.h"

bool	is_shortcuts_key(t_key_result key)
{
	if (key.key == KEY_CTRL_K)
		return (true);
	if (key.key == KEY_CTRL_U)
		return (true);
	if (key.key == KEY_CTRL_W)
		return (true);
	return (false);
}

void	handle_shortcuts(t_line *line, t_key_result key)
{
	if (key.key == KEY_CTRL_K)
		buffer_clear_from_cursor(line);
	else if (key.key == KEY_CTRL_U)
		buffer_clear_before_cursor(line);
	else if (key.key == KEY_CTRL_W)
		buffer_delete_word(line);
	}
