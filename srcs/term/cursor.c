/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 23:45:14 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/06 16:07:48 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/readline.h"

bool	is_word_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\0');
}

void	cursor_left(t_line *line)
{
	if (!line)
		return ;
	if (line->pos > 0)
		line->pos--;
}

void	cursor_right(t_line *line)
{
	if (!line)
		return ;
	if (line->pos < line->len)
		line->pos++;
}

void	cursor_home(t_line *line)
{
	if (!line)
		return;
	line->pos = 0;
}

void	cursor_end(t_line *line)
{
	if (!line)
		return ;
	line->pos = line->len;
}

void	cursor_word_foreward(t_line *line)
{
	if (!line || line->pos >- line->len)
		return ;

	while (line->pos < line->len && is_word_separator(line->buffer[line->pos]))
		line->pos++;
	while (line->pos < line->len && !is_word_separator(line->buffer[line->pos]))
		line->pos++;
}

void	cursor_word_backward(t_line *line)
{
	if (!line || line->pos == 0)
		return ;

	line->pos--;
	while (line->pos > 0 && is_word_separator(line->buffer[line->pos]))
		line->pos--;
	while (line->pos > 0 && !is_word_separator(line->buffer[line->pos - 1]))
		line->pos--;
}
