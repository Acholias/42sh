/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:43:50 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/06 12:37:01 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# include "term.h"

typedef enum e_key
{
	KEY_UNKNOWN,
	KEY_ENTER,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_ESC,
	KEY_CTRL_A,
	KEY_CTRL_B,
	KEY_CTRL_C,
	KEY_CTRL_D,
	KEY_CTRL_E,
	KEY_CTRL_F,
	KEY_CTRL_K,
	KEY_CTRL_L,
	KEY_CTRL_R,
	KEY_CTRL_T,
	KEY_CTRL_U,
	KEY_CTRL_W,
	KEY_CTRL_Y,
	KEY_CTRL_Z,
	KEY_CTRL_BACKSLASH,
	KEY_ARROW_UP,
	KEY_ARROW_DOWN,
	KEY_ARROW_RIGHT,
	KEY_ARROW_LEFT,
	KEY_CTRL_ARROW_LEFT,
	KEY_CTRL_ARROW_RIGHT,
	KEY_HOME,
	KEY_END,
	KEY_DELETE,
	KEY_PAGE_UP,
	KEY_PAGE_DOWN,
	KEY_ALT_B,
	KEY_ALT_C,
	KEY_ALT_D,
	KEY_ALT_F,
	KEY_ALT_L,
	KEY_ALT_T,
	KEY_ALT_U,
	KEY_ALT_BACKSPACE,
	KEY_ALT_LESS,
	KEY_ALT_GREATER
}	t_key;

typedef struct s_key_result
{
	t_key			key;
	unsigned char	character;
}	t_key_result;

// keys.c
t_key_result	get_key(void);

#endif
