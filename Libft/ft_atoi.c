/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:52:13 by lumugot           #+#    #+#             */
/*   Updated: 2024/10/11 15:13:13 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	size_t	index;
	size_t	conv;
	size_t	count;
	size_t	neg;

	index = 0;
	conv = 0;
	count = 0;
	neg = 0;
	while ((nptr[index] >= 9 && nptr[index] <= 13) || (nptr[index] == 32))
		index++;
	while (nptr[index] == '+' || nptr[index] == '-')
	{
		if (nptr[index] == '-')
			neg++;
		count++;
		index++;
	}
	while (nptr[index] >= 48 && nptr[index] <= 57)
		conv = conv * 10 + nptr[index++] - '0';
	if (count > 1)
		return (0);
	else if (neg == 1)
		return (-conv);
	return (conv);
}
