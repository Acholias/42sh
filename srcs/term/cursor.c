/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 23:45:14 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/05 23:50:26 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/readline.h"

void	cursor_left(t_line *line)
{
	if (!line)
		return ;
	if (line->pos > 0)
		line->pos--;
}

void	cursor_right(t_line *line)
{
	if (!line)
		return ;
	if (line->pos < line->len)
		line->pos++;
}

void	cursor_home(t_line *line)
{
	if (!line)
		return;
	line->pos = 0;
}

void	cursor_end(t_line *line)
{
	if (!line)
		return ;
	line->pos = line->len;
}
