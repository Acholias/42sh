/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:55:34 by lumugot           #+#    #+#             */
/*   Updated: 2024/10/18 10:38:34 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	int				size_str;
	char			*new_str;

	index = 0;
	size_str = 0;
	if (!s)
		return (NULL);
	while (s[size_str])
		size_str++;
	new_str = (char *)malloc(sizeof(char) * size_str + 1);
	if (!new_str)
		return (NULL);
	while (s[index])
	{
		new_str[index] = f(index, s[index]);
		index++;
	}
	new_str[index] = '\0';
	return (new_str);
}
