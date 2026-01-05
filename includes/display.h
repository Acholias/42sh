/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:04:03 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/05 20:08:38 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "term.h"

void	clear_line(void);
void	cursor_left(int n);
void	cursor_right(int n);
void	display_buffer(const char *buffer, int cursor_pos);

#endif
