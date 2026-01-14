/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:49:31 by lumugot           #+#    #+#             */
/*   Updated: 2024/10/18 08:30:18 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_nbr(int nbr)
{
	int	size;

	size = 0;
	if (nbr <= 0)
		size = 1;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int				f_size;
	unsigned int	f_nb;
	char			*conv;

	f_size = size_nbr(n);
	conv = malloc(sizeof(char) * (f_size + 1));
	if (!conv)
		return (NULL);
	conv[f_size] = '\0';
	if (n < 0)
	{
		conv[0] = '-';
		f_nb = -n;
	}
	else
		f_nb = n;
	if (n == 0)
		conv[0] = '0';
	while (f_nb > 0)
	{
		f_size--;
		conv[f_size] = f_nb % 10 + '0';
		f_nb = f_nb / 10;
	}
	return (conv);
}
