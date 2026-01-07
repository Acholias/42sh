/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:41:40 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/07 01:18:45 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/keys.h"

static t_key	parse_alt_key(unsigned char ch)
{
	if (ch == 'b')
		return (KEY_ALT_B);
	else if (ch == 'c')
		return (KEY_ALT_C);
	else if (ch == 'd')
		return (KEY_ALT_D);
	else if (ch == 'f')
		return (KEY_ALT_F);
	else if (ch == 'l')
		return (KEY_ALT_L);
	else if (ch == 't')
		return (KEY_ALT_T);
	else if (ch == 'u')
		return (KEY_ALT_U);
	else if (ch == '<')
		return (KEY_ALT_LESS);
	else if (ch == '>')
		return (KEY_ALT_GREATER);
	if (ch == 127 || ch == 8)
		return (KEY_ALT_BACKSPACE);
	return (KEY_UNKNOWN);
}

static t_key	parse_bracket_sequence(unsigned char first_char)
{
	unsigned char	seq[8];

	if (first_char >= '0' && first_char <= '9')
	{
		if (read(STDIN_FILENO, &seq[0], 1) != 1)
			return (KEY_ESC);
		if (seq[0] == '~')
		{
			if (first_char == '1')
				return (KEY_HOME);
			if (first_char == '3')
				return (KEY_DELETE);
			if (first_char == '4')
				return (KEY_END);
			if (first_char == '5')
				return (KEY_PAGE_UP);
			if (first_char == '6')
				return (KEY_PAGE_DOWN);
		}
		else if (first_char == '1' && seq[0] == ';')
		{
			if (read(STDIN_FILENO, &seq[1], 1) != 1)
				return (KEY_ESC);
			if (seq[1] == '5')
			{
				if (read(STDIN_FILENO, &seq[2], 1) != 1)
					return (KEY_ESC);
				if (seq[2] == 'D')
					return (KEY_CTRL_ARROW_LEFT);
				if (seq[2] == 'C')
					return (KEY_CTRL_ARROW_RIGHT);
				if (seq[2] == 'A')
					return (KEY_ARROW_UP);
				if (seq[2] == 'B')
					return (KEY_ARROW_DOWN);
			}
		}
		return (KEY_UNKNOWN);
	}
	else
	{
		if (first_char == 'A')
			return (KEY_ARROW_UP);
		if (first_char == 'B')
			return (KEY_ARROW_DOWN);
		if (first_char == 'C')
			return (KEY_ARROW_RIGHT);
		if (first_char == 'D')
			return (KEY_ARROW_LEFT);
		if (first_char == 'H')
			return (KEY_HOME);
		if (first_char == 'F')
			return (KEY_END);
	}
	return (KEY_UNKNOWN);
}

static t_key	parse_escape(void)
{
	unsigned char	seq[8];

	if (read(STDIN_FILENO, &seq[0], 1) != 1)
		return (KEY_ESC);
	if (seq[0] >= 'a' && seq[0] <= 'z')
		return (parse_alt_key(seq[0]));
	if (seq[0] == '<' || seq[0] == '>' || seq[0] == 127 || seq[0] == 8)
		return (parse_alt_key(seq[0]));
	if (seq[0] == '[')
	{
		if (read(STDIN_FILENO, &seq[1], 1) != 1)
			return (KEY_ESC);
		return (parse_bracket_sequence(seq[1]));
	}
	else if (seq[0] == 'O')
	{
		if (read(STDIN_FILENO, &seq[1], 1) != 1)
			return (KEY_ESC);
		if (seq[1] == 'H')
			return (KEY_HOME);
		if (seq[1] == 'F')
			return (KEY_END);
	}
	return (KEY_UNKNOWN);
}

t_key_result	get_key(void)
{
	t_key_result	res;
	unsigned char	ch;
	int				ret;

	res.key = KEY_UNKNOWN;
	res.character = 0;

	ret = read(STDIN_FILENO, &ch, 1);
	if (ret != 1)
	{
		if (ret == -1 && errno == EINTR)
			return (res);
		return (res);
	}

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
	else if (ch == 2)
		res.key = KEY_CTRL_B;
	else if (ch == 3)
		res.key = KEY_CTRL_C;
	else if (ch == 4)
		res.key = KEY_CTRL_D;
	else if (ch == 5)
		res.key = KEY_CTRL_E;
	else if (ch == 6)
		res.key = KEY_CTRL_F;
	else if (ch == 7)
		res.key = KEY_CTRL_G;
	else if (ch == 11)
		res.key = KEY_CTRL_K;
	else if (ch == 12)
		res.key = KEY_CTRL_L;
	else if (ch == 18)
		res.key = KEY_CTRL_R;
	else if (ch == 20)
		res.key = KEY_CTRL_T;
	else if (ch == 21)
		res.key = KEY_CTRL_U;
	else if (ch == 23)
		res.key = KEY_CTRL_W;
	else if (ch == 25)
		res.key = KEY_CTRL_Y;
	else if (ch == 26)
		res.key = KEY_CTRL_Z;
	else if (ch == 28)
		res.key = KEY_CTRL_BACKSLASH;
	else
		res.character = ch;
	
	return (res);
}
