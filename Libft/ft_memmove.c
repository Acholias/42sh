/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:40:13 by lumugot           #+#    #+#             */
/*   Updated: 2024/10/10 15:29:00 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			index;

	s1 = (unsigned char *) dest;
	s2 = (unsigned char *) src;
	index = 0;
	if (s1 == NULL && s2 == NULL)
		return (dest);
	if (dest > src)
	{
		while (n-- > 0)
			s1[n] = s2[n];
	}
	else
	{
		while (index < n)
		{
			s1[index] = s2[index];
			index++;
		}
	}
	return (dest);
}
