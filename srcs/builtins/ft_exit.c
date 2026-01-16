/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:31:38 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/16 13:39:47 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	ft_exit(char **argv, int last_exit_code)
{
	int	exit_code;

	printf("exit\n");
	exit_code = 0;
	if (argv[1])
	{
		exit_code = ft_atod(argv[1]);
		if (exit_code < 0 || exit_code > 255)
			exit_code = exit_code % 256;
	}
	else
		exit_code = last_exit_code;
	exit(exit_code);
	return (0);
}
