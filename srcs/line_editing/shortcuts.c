/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcuts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 23:53:49 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/06 19:00:44 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/readline.h"
#include "../../includes/keys.h"
#include "../../includes/display.h"

bool	is_shortcuts_key(t_key_result key)
{
	if (key.key == KEY_DELETE)
		return (true);
	if (key.key == KEY_CTRL_K || key.key == KEY_CTRL_U)
		return (true);
	if (key.key == KEY_CTRL_W || key.key == KEY_ALT_D)
		return (true);
	if (key.key == KEY_ALT_BACKSPACE)
		return (true);
	if (key.key == KEY_CTRL_T || key.key == KEY_ALT_T)
		return (true);
	if (key.key == KEY_CTRL_Y || key.key == KEY_CTRL_L)
		return (true);
	if (key.key == KEY_ALT_U || key.key == KEY_ALT_L || key.key == KEY_ALT_C)
		return (true);
	return (false);
}

void	handle_shortcuts(t_term *term, t_line *line, t_key_result key)
{
	if (key.key == KEY_DELETE)
		buffer_delete(line);
	else if (key.key == KEY_CTRL_K)
		buffer_clear_from_cursor(term, line);
	else if (key.key == KEY_CTRL_U)
		buffer_clear_before_cursor(term, line);
	else if (key.key == KEY_CTRL_W || key.key == KEY_ALT_BACKSPACE)
		buffer_delete_word(term, line);
	else if (key.key == KEY_ALT_D)
		buffer_delete_word_forward(term, line);
	else if (key.key == KEY_CTRL_T)
		buffer_transpose_chars(line);
	else if (key.key == KEY_ALT_T)
		buffer_transpose_words(line);
	else if (key.key == KEY_CTRL_Y)
		buffer_yank(term, line);
	else if (key.key == KEY_CTRL_L)
		display_refresh_with_clear(line);
	else if (key.key == KEY_ALT_U)
		buffer_uppercase_word(line);
	else if (key.key == KEY_ALT_L)
		buffer_lowercase_word(line);
	else if (key.key == KEY_ALT_C)
		buffer_capitalize_word(line);
}
