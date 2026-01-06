/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 23:20:11 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/05 23:41:50 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/readline.h"

void	buffer_init(t_line *line, int capacity)
{
	line->buffer = malloc(capacity);
	if (!line->buffer)
		return ;
	line->buffer[0] = '\0';
	line->pos = 0;
	line->len = 0;
	line->cap = capacity;
}

void	buffer_free(t_line *line)
{
	free(line->buffer);
	line->buffer[0] = '\0';
	line->pos = 0;
	line->len = 0;
	line->cap = 0;
}

void	buffer_insert(t_line *line, char c)
{
	if (line->len + 1 >= line->cap)
		return ;
	memmove(&line->buffer[line->pos + 1], &line->buffer[line->pos], line->len - line->pos + 1);
	line->buffer[line->pos] = c;
	line->pos++;
	line->len++;
}

void	buffer_backspace(t_line *line)
{
	if (line->pos == 0)
		return ;
	memmove(&line->buffer[line->pos - 1], &line->buffer[line->pos], line->len - line->pos + 1);
	line->pos--;
	line->len--;
}

void	buffer_delete(t_line *line)
{
	if (line->pos >= line->len)
		return ;
	memmove(&line->buffer[line->pos], &line->buffer[line->pos + 1], line->len - line->pos);
	line->len--;
}

void	buffer_clear_from_cursor(t_line *line)
{
	line->buffer[line->pos] = '\0';
	line->len = line->pos;
}

void	buffer_clear_before_cursor(t_line *line)
{
	memmove(line->buffer, &line->buffer[line->pos], line->len - line->pos + 1);
	line->len -= line->pos;
	line->pos = 0;
}

void	buffer_delete_word(t_line *line)
{
	int	start;

	if (line->pos == 0)
		return ;
	start = line->pos;
	while (start > 0 && line->buffer[start - 1] == ' ')
		start--;
	while (start > 0 && line->buffer[start - 1] != ' ')
		start--;
	memmove(&line->buffer[start], &line->buffer[line->pos], line->len - line->pos + 1);
	line->len -= (line->pos - start);
	line->pos = start;
}
