/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:43:50 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/06 11:56:52 by lumugot          ###   ########.fr       */
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
	KEY_CTRL_E,
	KEY_CTRL_K,
	KEY_CTRL_U,
	KEY_CTRL_W,
	KEY_CTRL_C,
	KEY_CTRL_D,
	KEY_ARROW_UP,
	KEY_ARROW_DOWN,
	KEY_ARROW_RIGHT,
	KEY_ARROW_LEFT,
	KEY_HOME,
	KEY_END,
	KEY_DELETE,
	KEY_PAGE_UP,
	KEY_PAGE_DOWN
}	t_key;

typedef struct s_key_result
{
	t_key			key;
	unsigned char	character;
}	t_key_result;

// keys.c
t_key_result	get_key(void);

#endif
