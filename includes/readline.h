/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 23:21:15 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/06 16:59:30 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include "term.h"
# include "keys.h"

# define MALLOC_FAILED NULL

typedef struct s_line
{
	char	*buffer;
	int		len;
	int		pos;
	int		cap;
}	t_line;

// buffer.c
void	buffer_init(t_line *line, int capacity);
void	buffer_free(t_line *line);
void	buffer_insert(t_line *line, char c);
void	buffer_backspace(t_line *line);
void	buffer_delete(t_line *line);
void	buffer_clear_from_cursor(t_term *term, t_line *line);   // CTRL + k
void	buffer_clear_before_cursor(t_term *term, t_line *line); // CTRL + U
void	buffer_delete_word(t_term *term, t_line *line);		  // CTRL + W
void	buffer_delete_word_forward(t_term *term, t_line *line);
void	buffer_transpose_chars(t_line *line);
void	buffer_yank(t_term *term, t_line *line);
void	buffer_uppercase_word(t_line *line);
void	buffer_lowercase_word(t_line *line);
void	buffer_capitalize_word(t_line *line);
void	buffer_transpose_words(t_line *line);

// cursor.c
bool	is_word_separator(char c);
void	cursor_left(t_line *line);
void	cursor_right(t_line *line);
void	cursor_home(t_line *line);
void	cursor_end(t_line *line);
void	cursor_word_foreward(t_line *line);
void	cursor_word_backward(t_line *line);

//shortcuts.c
bool	is_shortcuts_key(t_key_result key);
void	handle_shortcuts(t_line *line, t_key_result key);

// mouvements.c
bool	is_mouvements_key(t_key_result key);
void	handle_mouvements(t_line *line, t_key_result key);

#endif
