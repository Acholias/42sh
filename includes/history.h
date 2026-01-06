/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:36:36 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/06 21:11:17 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

# define HISTORY_SIZE 1000
# define HISTORY_FILE ".42sh_history"

# define MALLOC_FAILED NULL

typedef struct	s_history
{
	char	**entries;
	int		size;
	int		capacity;
	int		current;
	char	*temp_line;
}	t_history;

// history.c
t_history	*history_init(void);
void		history_free(t_history *hist);
void		history_add(t_history *hist, const char *line);
char		*history_prev(t_history *hist);
char		*history_next(t_history *hist);
void		history_reset_position(t_history *hist);
char		*history_get_current(t_history *hist);
void		history_save_temp(t_history *hist, const char *line);

// persistence.c
int			history_load(t_history *hist, const char *filepath);
int			history_save(t_history *hist, const char *filepath);

#endif
