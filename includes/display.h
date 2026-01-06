/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:04:03 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/06 18:58:21 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "term.h"
# include "readline.h"

void	display_clear_line(void);
void	display_clear_screen(void);
void	display_cursor_left(int n);
void	display_cursor_right(int n);
void	display_move_cursor_to(int position);
void	display_save_cursor(void);
void	display_restore_cursor(void);
int		display_get_terminal_width(void);
void	display_refresh_buffer(const t_line *line);
void	display_refresh_with_clear(const t_line *line);
void	dislay_newline(void);
void	display_newline(void);
void	display_prompt(void);
void	display_bell(void);

#endif
