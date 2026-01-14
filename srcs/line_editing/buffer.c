/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 23:20:11 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/14 13:56:30 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include <ctype.h>

static void	save_to_killring(t_term *term, const char *text, int len)
{
	if (!term)
		return ;
	if (term->killring)
		free(term->killring);
	term->killring = malloc(len + 1);
	if (!term->killring)
		return ;
	ft_memcpy(term->killring, text, len);
	term->killring[len] = '\0';
}

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
	line->buffer = NULL;
	line->pos = 0;
	line->len = 0;
	line->cap = 0;
}

void	buffer_insert(t_line *line, char c)
{
	if (line->len + 1 >= line->cap)
		return ;
	ft_memmove(&line->buffer[line->pos + 1], &line->buffer[line->pos], line->len - line->pos + 1);
	line->buffer[line->pos] = c;
	line->pos++;
	line->len++;
}

void	buffer_backspace(t_line *line)
{
	if (line->pos == 0)
		return ;
	ft_memmove(&line->buffer[line->pos - 1], &line->buffer[line->pos], line->len - line->pos + 1);
	line->pos--;
	line->len--;
}

void	buffer_delete(t_line *line)
{
	if (line->pos >= line->len)
		return ;
	ft_memmove(&line->buffer[line->pos], &line->buffer[line->pos + 1], line->len - line->pos);
	line->len--;
}

void	buffer_clear_from_cursor(t_term *term, t_line *line)
{
	if (line->pos < line->len)
		save_to_killring(term, &line->buffer[line->pos], line->len - line->pos);
	line->buffer[line->pos] = '\0';
	line->len = line->pos;
}

void	buffer_clear_before_cursor(t_term *term, t_line *line)
{
	if (line->pos > 0)
		save_to_killring(term, line->buffer, line->pos);
	ft_memmove(line->buffer, &line->buffer[line->pos], line->len - line->pos + 1);
	line->len -= line->pos;
	line->pos = 0;
}

void	buffer_delete_word(t_term *term, t_line *line)
{
	int start;

	if (line->pos == 0)
		return ;
	start = line->pos;
	while (start > 0 && is_word_separator(line->buffer[start - 1]))
		start--;
	while (start > 0 && !is_word_separator(line->buffer[start - 1]))
		start--;
	save_to_killring(term, &line->buffer[start], line->pos - start);
	ft_memmove(&line->buffer[start], &line->buffer[line->pos], line->len - line->pos + 1);
	line->len -= (line->pos - start);
	line->pos = start;
}

void	buffer_delete_word_forward(t_term *term, t_line *line)
{
	int	end;

	if (line->pos >= line->len)
		return ;
	end = line->pos;
	while (end < line->len && is_word_separator(line->buffer[end]))
		end++;	
	while (end < line->len && !is_word_separator(line->buffer[end]))
		end++;
	save_to_killring(term, &line->buffer[line->pos], end - line->pos);
	ft_memmove(&line->buffer[line->pos], &line->buffer[end], line->len - end + 1);
	line->len -= (end - line->pos);
}

void	buffer_transpose_chars(t_line *line)
{
	char	temp;

	if (line->len < 2)
		return ;
	if (line->pos == 0)
		line->pos = 1;
	else if (line->pos == line->len)
		line->pos--;
	temp = line->buffer[line->pos - 1];
	line->buffer[line->pos - 1] = line->buffer[line->pos];
	line->buffer[line->pos] = temp;
	if (line->pos < line->len)
		line->pos++;
}

void	buffer_yank(t_term *term, t_line *line)
{
	int	index;
	int	len;

	if(!term || !term->killring)
		return ;
	len = ft_strlen(term->killring);
	if (line->len + len >= line->cap)
		return ;
	ft_memmove(&line->buffer[line->pos + len], &line->buffer[line->pos], line->len - line->pos + 1);
	index = 0;
	while (index < len)
	{
		line->buffer[line->pos + index] = term->killring[index];
		index++;
	}
	line->pos += len;
	line->len += len;
}

void	buffer_uppercase_word(t_line *line)
{
	int	start;

	if (line->pos >= line->len)
		return ;
	start = line->pos;
	while (start < line->len && is_word_separator(line->buffer[start]))
		start++;
	while (start < line->len && !is_word_separator(line->buffer[start]))
	{
		line->buffer[start] = ft_toupper((unsigned char)line->buffer[start]);
		start++;
	}
	line->pos = start;
}

void	buffer_lowercase_word(t_line *line)
{
	int	start;

	if (line->pos >= line->len)
		return ;
	start = line->pos;
	while (start < line->len && is_word_separator(line->buffer[start]))
		start++;
	while (start < line->len && !is_word_separator(line->buffer[start]))
	{
		line->buffer[start] = ft_tolower((unsigned char)line->buffer[start]);
		start++;
	}
	line->pos = start;
}

void	buffer_capitalize_word(t_line *line)
{
	int		start;
	bool	first;

	if (line->pos >= line->len)
		return ;
	start = line->pos;
	while (start < line->len && is_word_separator(line->buffer[start]))
		start++;
	first = true;
	while (start < line->len && !is_word_separator(line->buffer[start]))
	{
		if (first == true)
		{
			line->buffer[start] = ft_toupper((unsigned char)line->buffer[start]);
			first = false;
	
		}
		else
			line->buffer[start] = ft_tolower((unsigned char )line->buffer[start]);
		start++;
	}
	line->pos = start;
}

static int	find_word_end_before(t_line *line, int position)
{
	int	end;

	end = position;
	while (end > 0 && is_word_separator(line->buffer[end - 1]))
		end--;
	return (end);
}

static int	find_word_start_before(t_line *line, int position)
{
	int	start;

	start = position;
	while (start > 0 && !is_word_separator(line->buffer[start- 1]))
		start--;
	return (start);
}

static bool	get_word_boundaries(t_line *line, int *w1_start, int *w1_end, int *w2_start, int *w2_end)
{
	*w2_end = find_word_end_before(line, line->pos);
	if (*w2_end == 0)
		return (false);
	*w2_start = find_word_start_before(line, *w2_end);
	*w1_end = find_word_end_before(line, *w2_start);
	if (*w1_end == 0)
		return (false);
	*w1_start = find_word_start_before(line, *w1_end);
	return (true);
}

static void	swap_word_in_buffer(t_line *line, int w1_start, int w1_end, int w2_start, int w2_end)
{
	char	*temp;
	int		w1_len;
	int		w2_len;
	int		gap_len;

	w1_len = w1_end - w1_start;
	w2_len = w2_end - w2_start;
	gap_len = w2_start - w1_end;
	temp = malloc(w2_len);
	if (!temp)
		return ;
	ft_memcpy(temp, &line->buffer[w2_start], w2_len);
	ft_memmove(&line->buffer[w1_start + w2_len + gap_len], &line->buffer[w1_start], w1_len);
	ft_memcpy(&line->buffer[w1_start], temp, w2_len);
	ft_memmove(&line->buffer[w1_start + w2_len], &line->buffer[w1_end], gap_len);
	free(temp);
}

void	buffer_transpose_words(t_line *line)
{
	int	w1_start;
	int	w1_end;
	int	w2_start;
	int	w2_end;

	if (line->pos == 0 || line->len < 2)
		return ;
	if (!get_word_boundaries(line, &w1_start, &w1_end, &w2_start, &w2_end))
		return ;
	swap_word_in_buffer(line, w1_start, w1_end, w2_start, w2_end);
}

void	buffer_reset(t_line *line)
{
	if (!line || !line->buffer)
		return ;
	line->buffer[0] ='\0';
	line->pos = 0;
	line->len = 0;
}
