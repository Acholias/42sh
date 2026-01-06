/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:27:09 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/06 19:33:30 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_H
# define TERM_H

# include <termios.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>

extern volatile sig_atomic_t g_interrupted;

typedef struct s_line t_line;

typedef	struct s_term
{
	struct	termios orig;
	struct	termios	raw;
	bool	enabled;
	char	*killring;
}	t_term;

# define PROMPT "\033[1;31m42sh> \033[0m"

// term_init.c
int		terminal_init(t_term *terminal);
int		terminal_enable(t_term *terminal);
int		terminal_disable(t_term *terminal);
int		manage_terminal(t_term	*terminal);

// signals.c
void	handle_sigint(int signal);
void	handle_sigwinch(int signal);
void	handle_sigtstp(int signal);
void	handle_sigcont(int signal);
void	signal_reset_buffer(t_line *line);
void	signal_handle_winch(t_line *line);
void	signal_set_current_line(t_line *line);
void	signal_set_current_term(t_term *term);
void	signals_init_interactive(void);
void	signals_restore_default(void);

#endif
