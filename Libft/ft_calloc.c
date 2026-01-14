/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:30:35 by lumugot           #+#    #+#             */
/*   Updated: 2024/10/18 13:13:36 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*tab;
	size_t	c;

	c = 0;
	if (nmemb <= 0 || size <= 0)
	{
		tab = (malloc(0));
		if (!tab)
			return (NULL);
		return (tab);
	}
	tab = malloc(nmemb * size);
	if (!tab)
		return (NULL);
	while (c < nmemb * size)
	{
		tab[c] = 0;
		c++;
	}
	return (tab);
}
