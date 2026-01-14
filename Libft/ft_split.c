/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 08:49:41 by lumugot           #+#    #+#             */
/*   Updated: 2024/10/20 14:05:29 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_tab(char **tab)
{
	int	iter;

	iter = 0;
	while (tab[iter])
	{
		free(tab[iter]);
		iter++;
	}
	free(tab);
}

static int	count_str(char const *str, char sep)
{
	int	move;
	int	count;
	int	check_str;

	move = 0;
	count = 0;
	while (str[move])
	{
		check_str = 0;
		while (str[move] != '\0' && str[move] == sep)
			move++;
		while (str[move] != '\0' && str[move] != sep)
		{
			if (check_str == 0)
			{
				count++;
				check_str = 1;
			}
			move++;
		}
	}
	return (count);
}

static char	*catch_substring(char const *s, int begin, int ending, char	**tab)
{
	int		p;
	char	*substring;

	p = 0;
	substring = malloc(sizeof(char) * (ending - begin + 1));
	if (!substring)
	{
		free_tab(tab);
		return (NULL);
	}
	while (begin < ending)
	{
		substring[p] = s[begin];
		begin++;
		p++;
	}
	substring[p] = '\0';
	return (substring);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		start;
	char	**tab_substrings;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	tab_substrings = malloc(sizeof(char *) * (count_str(s, c) + 1));
	if (!tab_substrings)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
			tab_substrings[j++] = catch_substring(s, start, i, tab_substrings);
	}
	tab_substrings[j] = NULL;
	return (tab_substrings);
}
