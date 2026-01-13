/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:36:15 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/13 18:56:48 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/history.h"

t_history	*history_init(void)
{
	t_history	*hist;

	hist = malloc(sizeof(t_history));
	if (!hist)
		return (MALLOC_FAILED);
	hist->capacity = 100;
	hist->entries = malloc(sizeof(char *) * hist->capacity);
	if (!hist->entries)
	{
		free(hist);
		return (MALLOC_FAILED);
	}
	hist->size = 0;
	hist->current = 0;
	hist->temp_line = NULL;
	return (hist);
}

void	history_free(t_history *hist)
{
	int	index;

	if (!hist)
		return ;
	index = 0;
	while (index < hist->size)
	{
		free(hist->entries[index]);
		index++;
	}
	free(hist->entries);
	if (hist->temp_line)
		free(hist->temp_line);
	free(hist);
}

static int	history_resize(t_history *hist)
{
	char	**new_entries;
	int		new_capacity;
	int		index;

	new_capacity = hist->capacity * 2;
	new_entries = malloc(sizeof(char *) * new_capacity);
	if (!new_entries)
		return (-1);
	index = 0;
	while (index < hist->size)
	{
		new_entries[index] = hist->entries[index];
		index++;
	}
	free(hist->entries);
	hist->entries = new_entries;
	hist->capacity = new_capacity;
	return (0);
}

void	history_add(t_history *hist, const char *line)
{
	char	*dup;

	if (!hist || !line || !*line)
		return ;
	if (hist->size > 0 && strcmp(hist->entries[hist->size - 1], line) == 0)
		return ;
	if (hist->size >= hist->capacity)
	{
		if (history_resize(hist) == -1)
			return ;
	}
	dup = strdup(line);
	if (!dup)
		return ;
	hist->entries[hist->size] = dup;
	hist->size++;
	history_reset_position(hist);
}

char	*history_prev(t_history *hist)
{
	if (!hist || hist->size == 0)
		return (NULL);
	if (hist->current == hist->size)
	{
		if (hist->temp_line)
			free(hist->temp_line);
		hist->temp_line = NULL;
	}
	if (hist->current > 0)
		hist->current--;
	return (hist->entries[hist->current]);
}

char	*history_next(t_history *hist)
{
	if (!hist || hist->size == 0)
		return (NULL);
	if (hist->current < hist->size)
		hist->current++;
	if (hist->current == hist->size)
		return (hist->temp_line ? hist->temp_line : "");
	return (hist->entries[hist->current]);
}

void	history_reset_position(t_history *hist)
{
	if (!hist)
		return ;
	hist->current = hist->size;
	if (hist->temp_line)
	{
		free(hist->temp_line);
		hist->temp_line = NULL;
	}
}

char	*history_get_current(t_history *hist)
{
	if (!hist || hist->size == 0)
		return (NULL);
	if (hist->current >= hist->size)
		return (hist->temp_line);
	return (hist->entries[hist->current]);
}

void	history_save_temp(t_history *hist, const char *line)
{
	if (!hist)
		return ;
	if (hist->temp_line)
		free(hist->temp_line);
	hist->temp_line = strdup(line);
}

char	*history_goto_first(t_history *hist)
{
	if (!hist || hist->size == 0)
		return (NULL);
	if (hist->current == hist->size)
		history_save_temp(hist, "");
	hist->current = 0;
	return (hist->entries[0]);
}

char	*history_goto_last(t_history *hist)
{
	if (!hist || hist->size == 0)
		return (NULL);
	hist->current = hist->size;
	if (hist->temp_line)
	 return (hist->temp_line);
	return ("");
}
