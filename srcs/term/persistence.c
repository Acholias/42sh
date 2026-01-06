/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   persistence.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:45:26 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/07 00:08:55 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/history.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static char	*get_history_filepath(void)
{
	char	*home;
	char	*filepath;
	size_t	len;

	home = getenv("HOME");
	if (!home)
		return (NULL);
	len = strlen(home) + strlen(HISTORY_FILE) + 2;
	filepath = malloc(len);
	if (!filepath)
		return (MALLOC_FAILED);
	snprintf(filepath, len, "%s/%s", home, HISTORY_FILE);
	return (filepath);
}

int	history_save(t_history *hist, const char *filepath)
{
	FILE	*file;
	int		index;

	if (!hist || !filepath)
		return (-1);
	file = fopen(filepath, "w");
	if (!file)
		return (-1);
	index = 0;
	while (index < hist->size)
	{
		fprintf(file, "%s\n", hist->entries[index]);
		index++;
	}
	fclose(file);
	return (0);
}

int	history_load(t_history *hist, const char *filepath)
{
	FILE	*file;
	char	*line;
	size_t	len;
	ssize_t	read_len;

	if (!hist)
		return (-1);
	file = fopen(filepath, "r");
	if (!file)
		return (0);
	line = NULL;
	len = 0;
	while ((read_len = getline(&line, &len, file)) != -1)
	{
		if (read_len > 0 && line[read_len - 1] == '\n')
			line[read_len - 1] = '\0';
		if (*line)
			history_add(hist, line);
	}
	free(line);
	fclose(file);
	return (0);
}

int	history_save_default(t_history *hist)
{
	char	*filepath;
	int		ret;

	filepath = get_history_filepath();
	if (!filepath)
		return (-1);
	ret = history_save(hist, filepath);
	free(filepath);
	return (ret);
}

int	history_load_default(t_history *hist)
{
	char	*filepath;
	int		ret;

	filepath = get_history_filepath();
	if (!filepath)
		return (-1);
	ret = history_load(hist, filepath);
	free(filepath);
	return (ret);
}
