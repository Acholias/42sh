/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:17:20 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/16 17:32:49 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	ft_echo(char **argv)
{
	int		index;
	bool	newline;

	newline = true;
	index = 1;
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
	{
		newline = false;
		index = 2;
	}
	while (argv[index])
	{
		printf("\r%s", argv[index]);
		if (argv[index + 1])
			printf(" ");
		index++;
	}
	if (newline)
		printf("\n");
	return (0);
}
