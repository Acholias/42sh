/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:35:21 by lumugot           #+#    #+#             */
/*   Updated: 2024/10/12 09:23:27 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			index;
	unsigned char	letter;
	unsigned char	*str;

	index = 0;
	letter = (unsigned char)c;
	str = (unsigned char *)s;
	if (n == 0)
		return (NULL);
	while (index < n && str[index] != letter)
		index++;
	if (index < n && str[index] == letter)
		return ((unsigned char *)&str[index]);
	return (NULL);
}
