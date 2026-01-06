/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:49:42 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/06 00:51:16 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

volatile sig_atomic_t g_interrupted = 0;

void	handle_signal(int signal)
{
	(void)signal;
	g_interrupted = 1;
}
