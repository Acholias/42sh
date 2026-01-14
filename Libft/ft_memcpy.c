/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:25:27 by lumugot           #+#    #+#             */
/*   Updated: 2024/10/10 10:46:04 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			index;
	unsigned char	*s1;
	unsigned char	*s2;

	index = 0;
	s1 = (unsigned char *) dest;
	s2 = (unsigned char *) src;
	if (s1 == NULL && s2 == NULL)
		return (dest);
	while (index < n)
	{
		s1[index] = s2[index];
		index++;
	}
	return (dest);
}
