/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:53:39 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/14 15:15:20 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	free_string_array(char **array)
{
	int	index;

	if (!array)
		return ;
	index = 0;
	while (array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
}

static int	count_brace_elements(const char *str, int start)
{
	int	count;
	int index;
	int	depth;

	count = 1;
	index = start + 1;
	depth = 0;
	while (str[index] && (str[index] != '}' || depth > 0))
	{
		if (str[index] == '{')
			depth++;
		else if (str[index] == '}')
			depth--;
		else if (str[index] == ',' && depth == 0)
			count++;
		index++;
	}
	return (count);
}

static char	**extract_elements(const char *str, int start, int *end)
{
	char	**elements;
	int		count;
	int		index;
	int		j;
	int		start_element;
	int		depth;

	count = count_brace_elements(str, start);
	elements = malloc(sizeof(char *) * (count + 1));
	if (!elements)
		return (MALLOC_FAILED);
	index = start + 1;
	j = 0;
	start_element = index;
	depth = 0;
	while (str[index] && (str[index] != '}' || depth > 0))
	{
		if (str[index] == '{')
			depth++;
		else if (str[index] == '}')
			depth--;
		else if (str[index] == ',' && depth == 0)
		{
			elements[j] = ft_strndup(str + start_element, index - start_element);
			if (!elements[j])
				return (MALLOC_FAILED);
			j++;
			start_element = index + 1;
		}
		index++;
	}
	elements[j] = ft_strndup(str + start_element, index - start_element);
	if (!elements[j])
		return (MALLOC_FAILED);
	elements[j + 1] = NULL;
	*end = index;
	return (elements);
}

static bool	is_valid_brace_expansion(const char *str, int start)
{
	int	index;
	int	comma_count;
	int	depth;

	index = start + 1;
	comma_count = 0;
	depth = 0;
	while (str[index] && (str[index] != '}' || depth > 0))
	{
		if (str[index] == '{')
			depth++;
		else if (str[index] == '}')
			depth--;
		else if (str[index] == ',' && depth == 0)
			comma_count++;
		index++;
	}
	return (str[index] == '}' && comma_count > 0);
}

static char	**build_expansion(const char *prefix, char **elements, const char *suffix)
{
	char	**result;
	int		index;
	int		count;
	char	*temp;

	count = 0;
	while (elements[count])
		count++;
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (MALLOC_FAILED);
	index = 0;
	while (index < count)
	{
		temp = ft_strjoin(prefix, elements[index]);
		result[index] = ft_strjoin(temp, suffix);
		free(temp);
		index++;
	}
	result[index] = NULL;
	return (result);
}
