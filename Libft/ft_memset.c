/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:42:11 by lumugot           #+#    #+#             */
/*   Updated: 2024/10/13 14:10:14 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	size;
	char	*str;

	size = 0;
	str = (char *) s;
	while (size < n)
	{
		str[size] = c;
		size++;
	}
	return (s);
}
