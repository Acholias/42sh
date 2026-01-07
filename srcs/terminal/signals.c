/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:49:42 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/07 16:21:32 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/readline.h"
#include "../../includes/display.h"
#include <signal.h>

volatile sig_atomic_t	g_interrupted = 0;
volatile sig_atomic_t	g_winch_received = 0;

static t_line			*g_current_line = NULL;
static t_term			*g_current_term = NULL;

void	signal_set_current_line(t_line *line)
{
	g_current_line = line;
}

void	signal_set_current_term(t_term *term)
{
	g_current_term = term;
}

void	handle_sigint(int signal)
{
	(void)signal;
	g_interrupted = 1;
}

void	handle_sigwinch(int signal)
{
	(void)signal;
	g_winch_received = 1;
}

void	handle_sigtstp(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	
	if (g_current_term)
		tcsetattr(STDIN_FILENO, TCSANOW, &g_current_term->orig);
	
	signal(SIGTSTP, SIG_DFL);
	kill(getpid(), SIGTSTP);
}

void	handle_sigcont(int signal)
{
	struct sigaction	sa;

	(void)signal;
	
	if (g_current_term)
		tcsetattr(STDIN_FILENO, TCSANOW, &g_current_term->raw);
	
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_sigtstp;
	sigaction(SIGTSTP, &sa, NULL);
	
	display_prompt();
	if (g_current_line)
		display_refresh_buffer(g_current_line);
}

void	signal_reset_buffer(t_line *line)
{
	write(STDOUT_FILENO, "^C", 2);
	g_interrupted = 0;
	line->pos = 0;
	line->len = 0;
	if (line->buffer)
		line->buffer[0] = '\0';
	write(STDOUT_FILENO, "\n\r", 2);
	display_prompt();
}

void	signal_handle_winch(t_line *line)
{
	if (!g_winch_received)
		return ;
	g_winch_received = 0;
	if (line)
		display_refresh_buffer(line);
}

void	signals_init_interactive(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_sigint;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = handle_sigwinch;
	sigaction(SIGWINCH, &sa, NULL);

	sa.sa_handler = handle_sigtstp;
	sigaction(SIGTSTP, &sa, NULL);

	sa.sa_handler = handle_sigcont;
	sigaction(SIGCONT, &sa, NULL);

	// signal(SIGQUIT, SIG_IGN);
}

void	signals_restore_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGCONT, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
}
