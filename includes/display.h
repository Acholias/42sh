/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:04:03 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/05 23:46:16 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "term.h"
# include "readline.h"

void	display_clear_line(void);
void	display_cursor_left(int n);
void	display_cursor_right(int n);
void	display_refresh_buffer(const t_line *line);

#endif
