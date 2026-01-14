/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:07:10 by lumugot           #+#    #+#             */
/*   Updated: 2024/10/16 16:20:00 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size_str;
	size_t	i;
	size_t	j;
	char	*ex_str;

	i = start;
	j = 0;
	if (!s)
		return (NULL);
	size_str = ft_strlen(s);
	if (start >= size_str || len == 0)
		return ((char *)ft_calloc(1, sizeof(char)));
	if (start + len > size_str)
		len = size_str - start;
	ex_str = malloc(sizeof(char) * len + 1);
	if (!ex_str)
		return (NULL);
	ex_str[0] = '\0';
	while (j < len && i < size_str)
		ex_str[j++] = s[i++];
	ex_str[j] = '\0';
	return (ex_str);
}
