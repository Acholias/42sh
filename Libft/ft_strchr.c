/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:54:47 by lumugot           #+#    #+#             */
/*   Updated: 2024/10/11 13:59:01 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	letter;

	letter = c;
	while (*s && *s != letter)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	if (*s == letter)
		return ((char *)s);
	return (NULL);
}
