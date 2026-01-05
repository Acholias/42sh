#ifndef TERM_H
# define TERM_H

# include <termios.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>

typedef	struct s_term
{
	struct	termios orig;
	struct	termios	raw;
	bool	enabled;

}	t_term;

// term_init.c
int		terminal_init(t_term *terminal);
int		terminal_enable(t_term *terminal);
int		terminal_disable(t_term *terminal);

#endif
