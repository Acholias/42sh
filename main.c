/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:33:34 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/05 18:24:54 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/term.h"

int	main(void)
{
	t_term	terminal;
	char	character;

	if (terminal_init(&terminal) == -1)
		return (-1);
	if (terminal_enable(&terminal) == -1)
		return (-1);
	while (read(STDIN_FILENO, &character, 1) == 1)
	{
		if (character == 27)
			break ;
		write(STDOUT_FILENO, &character, 1);
	}
	terminal_disable(&terminal);
	close(6); //  WSL's terminal fd open 
	return (0);
}
