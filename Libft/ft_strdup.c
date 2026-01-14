/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:37:54 by lumugot           #+#    #+#             */
/*   Updated: 2024/10/10 16:51:59 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	index;
	size_t	count;
	char	*dup;

	index = 0;
	count = 0;
	while (s[count] && s[count] != '\0')
		count++;
	dup = malloc(sizeof(char) * count + 1);
	if (!dup)
		return (NULL);
	while (s[index] && s[index] != '\0')
	{
		dup[index] = s[index];
		index++;
	}
	dup[index] = '\0';
	return (dup);
}
