/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 23:19:02 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/13 19:53:00 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	handle_history_navigation(t_history *hist, t_line *line, t_key_result key)
{
	char	*entry;

	if (key.key == KEY_ARROW_UP || key.key == KEY_PAGE_UP)
	{
		if (hist->current == hist->size)
			history_save_temp(hist, line->buffer);
		entry = history_prev(hist);
		if (entry)
		{
			ft_strcpy(line->buffer, entry);
			line->len = ft_strlen(entry);
			line->pos = line->len;
			display_refresh_buffer(line);
		}
	}
	else if (key.key == KEY_ARROW_DOWN || key.key == KEY_PAGE_DOWN)
	{
		entry = history_next(hist);
		if (entry)
		{
			ft_strcpy(line->buffer, entry);
			line->len = ft_strlen(entry);
			line->pos = line->len;
		}
		else
		{
			if (hist->temp_line)
			{
				ft_strcpy(line->buffer, hist->temp_line);
				line->len = ft_strlen(hist->temp_line);
				line->pos = line->len;
			}
			else
			{
				line->buffer[0] = '\0';
				line->pos = 0;
				line->len = 0;
			}
		}
		display_refresh_buffer(line);
	}
}

static void	handle_history_jump(t_history *hist, t_line *line, t_key_result key)
{
	char	*entry;

	if (key.key == KEY_ALT_LESS)
	{
		entry = history_goto_first(hist);
		if (entry)
		{
			ft_strcpy(line->buffer, entry);
			line->len = ft_strlen(entry);
			line->pos = line->len;
			display_refresh_buffer(line);
		}
	}
	else if (key.key == KEY_ALT_GREATER)
	{
		entry = history_goto_last(hist);
		if (entry)
		{
			ft_strcpy(line->buffer, entry);
			line->len = ft_strlen(entry);
			line->pos = line->len;
		}
		else
		{
			line->buffer[0] = '\0';
			line->pos = 0;
			line->len = 0;
		}
		display_refresh_buffer(line);
	}
}

static void	catch_ctrl_backslash(t_term *term, t_history *hist, t_line *line)
{
	history_save_default(hist);
	buffer_free(line);
	history_free(hist);
	if (term)
		terminal_disable(term);
	write(STDOUT_FILENO, "^\\", 2);
	close(6); // WSL PROTECTION
	signal(SIGQUIT, SIG_DFL);
	raise(SIGQUIT);
}

static bool	handle_special_keys(t_term *term, t_line *line, t_history *hist,
			t_key_result key, t_exec_ctx *exec_ctx)
{
	char	*result;

	if (key.key == KEY_CTRL_D)
		return (false);
	if (key.key == KEY_CTRL_BACKSLASH)
		catch_ctrl_backslash(term, hist, line);
	if (key.key == KEY_CTRL_R)
	{
		result = history_search(hist);
		if (result)
		{
			ft_strcpy(line->buffer, result);
			line->len = ft_strlen(result);
			line->pos = line->len;
			free(result);
		}
		display_prompt();
		display_refresh_buffer(line);
		return (true);
	}
	if (key.key == KEY_ALT_GREATER || key.key == KEY_ALT_LESS)
	{
		handle_history_jump(hist, line, key);
		return (true);
	}
	if (key.key == KEY_ARROW_UP || key.key == KEY_ARROW_DOWN || key.key == KEY_PAGE_UP || key.key == KEY_PAGE_DOWN)
	{
		handle_history_navigation(hist, line, key);
		return (true);
	}
	if (key.key == KEY_ENTER)
	{
		display_newline();
		if (line->len > 0)
		{
			history_add(hist, line->buffer);
			t_token	*token = lexer_tokenizer(line->buffer);
			#ifdef DEBUG
			if (token)
				token_print_all(token);
			#endif
			t_ast_node	*ast = parser_build_ast(token);
			#ifdef DEBUG
			if (ast)
				ast_print_debug(ast);
			#endif
			if (ast)
			{
				executor_run(ast, exec_ctx);
				free_ast(ast);
			}
			token_free(token);
		}
		fflush(stdout);
		history_reset_position(hist);
		display_prompt();
		buffer_reset(line);
		return (true);
	}
	if (is_shortcuts_key(key))
		handle_shortcuts(term, line, key);
	else if (is_mouvements_key(key))
		handle_mouvements(line, key);
	else if (key.key == KEY_BACKSPACE)
		buffer_backspace(line);
	else if (key.key == KEY_UNKNOWN && key.character)
		buffer_insert(line, key.character);
	return (true);
}

static void	handle_interruption(t_line *line, t_history *hist)
{
	signal_reset_buffer(line);
	history_reset_position(hist);
}

static int	init_readline_context(t_term *term, t_line *line, t_history **hist)
{
	*hist =	history_init();
	if (!*hist)
		return (-1);

	history_load_default(*hist);
	buffer_init(line, 1024);
	signal_set_current_line(line);
	signal_set_current_term(term);
	display_prompt();
	return (0);
}

void	cleanup_readline_context(t_line *line, t_history *hist)
{
	history_save_default(hist);
	signal_set_current_line(NULL);
	signal_set_current_term(NULL);
	buffer_free(line);
	history_free(hist);
}

int	readline_loop(t_term *terminal, t_exec_ctx *exec_ctx)
{
	t_key_result	key;
	t_line			line;
	t_history		*hist;

	if (!terminal || !exec_ctx)
		return (-1);
	if (init_readline_context(terminal, &line, &hist) == -1)
		return (-1);
	while (1)
	{
		if (g_interrupted)
		{
			handle_interruption(&line, hist);
			continue ;
		}
		signal_handle_winch(&line);
		key = get_key();
		if (!handle_special_keys(terminal, &line, hist, key, exec_ctx))
			break ;
		display_refresh_buffer(&line);
	}
	cleanup_readline_context(&line, hist);
	return (0);
}
