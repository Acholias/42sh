/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:57:23 by lumugot           #+#    #+#             */
/*   Updated: 2024/10/12 20:42:37 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t			i;
	size_t			c;
	unsigned char	*init_str;
	unsigned char	*search_str;

	i = 0;
	init_str = (unsigned char *)big;
	search_str = (unsigned char *)little;
	if (len == 0 && (!big || !little))
		return ("\0");
	if (search_str[0] == '\0')
		return ((char *)init_str);
	while (init_str[i] != '\0' && i < len)
	{
		c = 0;
		while (search_str[c] == init_str[i + c] && i + c < len)
		{
			if (search_str[c + 1] == '\0')
				return ((char *)init_str + i);
			c++;
		}
		i++;
	}
	return (NULL);
}
