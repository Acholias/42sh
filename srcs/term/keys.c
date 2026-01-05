/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:41:40 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/05 19:48:12 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/keys.h"

static t_key	parse_escape(void)
{
	unsigned char	seq[8];

	if (read(STDIN_FILENO, &seq[0], 1) != 1) return (KEY_ESC);
	if (read(STDIN_FILENO, &seq[1], 1) != 1) return (KEY_ESC);

	if (seq[0] == '[')
	{
		if (seq[1] >= '0' && seq[1] <= '9')
		{
			if (read(STDIN_FILENO, &seq[2], 1) != 1) return (KEY_ESC);
			if (seq[2] == '~')
			{
				if (seq[1] == '1') return (KEY_HOME);
				if (seq[1] == '3') return (KEY_DELETE);
				if (seq[1] == '4') return (KEY_END);
				if (seq[1] == '5') return (KEY_PAGE_UP);
				if (seq[1] == '6') return (KEY_PAGE_DOWN);
			}
			return (KEY_UNKNOWN);
		}
		else
		{
			if (seq[1] == 'A') return (KEY_ARROW_UP);
			if (seq[1] == 'B') return (KEY_ARROW_DOWN);
			if (seq[1] == 'C') return (KEY_ARROW_RIGHT);
			if (seq[1] == 'D') return (KEY_ARROW_LEFT);
			if (seq[1] == 'H') return (KEY_HOME);
			if (seq[1] == 'F') return (KEY_END);
		}
	}
	else if (seq[0] == 'O')
	{
		if (seq[1] == 'H') return (KEY_HOME);
		if (seq[1] == 'F') return (KEY_END);
	}
	return (KEY_UNKNOWN);
}

t_key_result	get_key(void)
{
	t_key_result	res;
	unsigned char	ch;

	res.key = KEY_UNKNOWN;
	res.character = 0;

    if (read(STDIN_FILENO, &ch, 1) != 1)
        return (res);

    if (ch == 27)
    {
		res.key = parse_escape();
		return (res);
    }

	if (ch == '\n' || ch == '\r')
		res.key = KEY_ENTER;
	else if (ch == 127 || ch == 8)
		res.key = KEY_BACKSPACE;
	else if (ch == 9)
		res.key = KEY_TAB;
	else if (ch == 1)
		res.key = KEY_CTRL_A;
	else if (ch == 5)
		res.key = KEY_CTRL_E;
	else if (ch == 11)
		res.key = KEY_CTRL_K;
	else if (ch == 21)
		res.key = KEY_CTRL_U;
	else if (ch == 23)
		res.key = KEY_CTRL_W;
	else if (ch == 4)
		res.key = KEY_CTRL_D;
	else if (ch == 3)
		res.key = KEY_CTRL_C;
	else
		res.character = ch;
	return (res);
}
