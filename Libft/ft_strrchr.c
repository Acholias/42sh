/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:01:53 by lumugot           #+#    #+#             */
/*   Updated: 2024/10/16 09:14:00 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				index;
	unsigned char	letter;

	index = 0;
	letter = c;
	while (s[index] != '\0')
		index++;
	while (index >= 0)
	{
		if (s[index] == letter)
			return ((char *)s + index);
		index--;
	}
	return (NULL);
}
