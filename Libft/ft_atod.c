/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:48:55 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/17 22:17:19 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	after_point(char *nptr, double res, int index)
{
	int	e;

	e = 0;
	while (ft_isdigit(nptr[index]))
	{
		res = (res * 10.) + (nptr[index] - '0');
		index++;
		e--;
	}
	while (e < 0)
	{
		res /= 10.;
		e++;
	}
	return (res);
}

double	ft_atod(char *nptr)
{
	int		i;
	int		sign;
	double	res;

	i = 0;
	sign = 1;
	res = 0.0;
	while (nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
		sign *= -1;
	i += (nptr[i] == '+' || nptr[i] == '-');
	while (ft_isdigit(nptr[i]))
	{
		res = (res * 10.) + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] != '.')
		return (res * sign);
	res = after_point(nptr, res, ++i);
	return (res * sign);
}
