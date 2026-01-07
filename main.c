/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:33:34 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/06 23:47:55 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/display.h"
#include "includes/term.h"

int main(void)
{
	t_term			terminal;

	if (terminal_init(&terminal) == -1)
		return (-1);
	if (terminal_enable(&terminal) == -1)
	{
		terminal_disable(&terminal);
		return (-1);
	}
	readline_loop(&terminal);
	terminal_disable(&terminal);
	display_newline();
	close(6);
	return (0);
}
