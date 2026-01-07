/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:26:55 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/07 01:20:40 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/history.h"
#include "../../includes/display.h"
#include "../../includes/keys.h"
#include <unistd.h>

static void	display_search_prompt(t_search *search, const char *match)
{
	display_clear_line();
	write(STDOUT_FILENO, "(reverse-i-search)`", 19);
	if (search->term_len > 0)
		write(STDOUT_FILENO, search->search_term, search->term_len);
	write(STDOUT_FILENO, "': ", 3);
	if (match)
		write(STDOUT_FILENO, match, strlen(match));
}

static char	*find_match(t_history *hist, const char *term, int start_pos)
{
	int	index;

	if (!term || !*term)
		return (NULL);
	index = start_pos;
	while (index >= 0)
	{
		if (strstr(hist->entries[index], term))
			return (hist->entries[index]);
		index--;
	}
	return (NULL);
}

static void	search_add_char(t_search *search, t_history *hist, char c)
{
	char	*match;
	int		index;

	if (search->term_len >= 255)
		return ;
	search->search_term[search->term_len] = c;
	search->term_len++;
	search->search_term[search->term_len] = '\0';
	match = find_match(hist, search->search_term, hist->size - 1);
	if (match)
	{
		index = 0;
		while (index < hist->size && hist->entries[index] != match)
			index++;
		search->match_index = index;
	}
	display_search_prompt(search, match);
}

static void	search_backspace(t_search *search, t_history *hist)
{
	char	*match;
	int		index;

	if (search->term_len == 0)
		return ;
	search->term_len--;
	search->search_term[search->term_len] = '\0';
	if (search->term_len == 0)
		match = NULL;
	else
		match = find_match(hist, search->search_term, hist->size - 1);
	if (match)
	{
		index = 0;
		while (index < hist->size && hist->entries[index] != match)
			index++;
		search->match_index = index;
	}
	display_search_prompt(search, match);
}

static void	search_next_match(t_search *search, t_history *hist)
{
	char	*match;
	int		index;

	if (search->match_index <= 0)
		return ;
	match = find_match(hist, search->search_term, search->match_index - 1);
	if (match)
	{
		index = 0;
		while (index < hist->size && hist->entries[index] != match)
			index++;
		search->match_index = index;
		display_search_prompt(search, match);
	}
}

char	*history_search(t_history *hist)
{
	t_search		search;
	t_key_result	key;
	char			*match;
	char			*result;

	memset(&search, 0, sizeof(search));
	search.active = true;
	search.match_index = hist->size - 1;
	match = NULL;
	display_search_prompt(&search, match);
	while (search.active)
	{
		key = get_key();
		if (key.key == KEY_CTRL_R)
			search_next_match(&search, hist);
		else if (key.key == KEY_BACKSPACE)
			search_backspace(&search, hist);
		else if (key.key == KEY_ENTER)
		{
			match = find_match(hist, search.search_term, hist->size - 1);
			result = match ? strdup(match) : strdup("");
			display_clear_line();
			return (result);
		}
		else if (key.key == KEY_ESC || key.key == KEY_CTRL_C || key.key == KEY_CTRL_G)
		{
			display_clear_line();
			return (NULL);
		}
		else if (key.key == KEY_UNKNOWN && key.character >= 32 && key.character <= 126)
			search_add_char(&search, hist, key.character);
	}
	return (NULL);
}
