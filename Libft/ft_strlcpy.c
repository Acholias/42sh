/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 09:26:45 by lumugot           #+#    #+#             */
/*   Updated: 2024/10/12 10:31:24 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char	*dst, const char *src, size_t size)
{
	size_t	index;
	size_t	init_size;

	index = 0;
	init_size = ft_strlen(src);
	if (!dst || !src)
		return (0);
	if (size > 0)
	{
		while (src[index] != '\0' && index < size -1)
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	return (init_size);
}
