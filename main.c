/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:33:34 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/05 19:48:38 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/keys.h"
#include "includes/term.h"
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	t_term			terminal;
	t_key_result	key;

	if (terminal_init(&terminal) == -1) return -1;
	if (terminal_enable(&terminal) == -1) return -1;

	while (1)
	{
		key = get_key();
		if (key.key == KEY_ESC || key.key == KEY_CTRL_D)
			break;
		
		if (key.key != KEY_UNKNOWN && key.key < KEY_CTRL_A)
			printf("Special key pressed: [%d]\n", key.key);
		
		if (key.key == KEY_UNKNOWN && key.character)
			write(STDOUT_FILENO, &key.character, 1);

		fflush(stdout);
	}
	terminal_disable(&terminal);
	close (6); // WSL terminal's fd
	return (0);
}
