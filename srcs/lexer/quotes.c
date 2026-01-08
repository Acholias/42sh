/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:44:27 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/08 17:51:44 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static bool	is_word_delimiter(char c)
{
	return (c == '\0' || c == ' ' || c == '\t' || c == '\n' || is_operator_char(c));
}

static const char	*find_closing_quote(const char *str, char quote)
{
	str++;
	while (*str && *str != quote)
	{
		if (quote == '"' && *str == '\\' && str[1])
			str++;
		str++;
	}
	if (*str == quote)
		return (str);
	return (NULL);
}

bool	check_quotes_closed(const char *input)
{
	const char	*closing;

	while (*input)
	{
		if (*input == '"' || *input == '\'')
		{
			closing = find_closing_quote(input, *input);
			if (!closing)
			{
				fprintf(stderr ,"\r42sh: syntax error: unclosed quote\n");
				return (NULL);
			}
			input = closing + 1;
		}
		else if (*input== '\\' && input[1])
			input += 2;
		else
			input++;
	}
	return (true);
}

static int	size_between_quotes(const char *str, char quote)
{
	int	size;

	size = 0;
	str++;
	while (*str && *str != quote)
	{
		if (quote == '"' && *str == '\\')
		{
			str++;
			if (*str == '$' || *str == '`' || *str == '"' || *str == '\\' || *str == '\n')
			{
				size++;
				str++;
			}
			else
			{
				size += 2;
				if (*str)
					str++;
			}
		}
		else
		{
			size++;
			str++;
		}
	}
	return (size);
}

static int	calculate_word_length(const char *str)
{
	int			res;
	const char	*closing;

	res = 0;
	while (*str && !is_word_delimiter(*str))
	{
		if (*str == '"' || *str == '\'')
		{
			closing = find_closing_quote(str, *str);
			if (!closing)
				return (0);
			res += size_between_quotes(str, *str);
			str = closing + 1;
		}
		else if (*str == '\\' && str[1] && !is_word_delimiter(str[1]))
		{
			res++;
			str += 2;
		}
		else
		{
			res++;
			str++;
		}
	}
	return (res);
}

static char	*copy_str_between_dquotes(const char **src, char *dest)
{
	(*src)++;
	while (**src && **src != '"')
	{
		if (**src == '\\')
		{
			(*src)++;
			if (**src == '$' || **src == '`' || **src == '"' || **src == '\\' || **src == '\n')
			{
				*dest++ = **src;
				(*src)++;
			}
			else
			{
				*dest++ = '\\';
				if (**src)
					*dest++ = *(*src)++;
			}
		}
		else
			*dest++ = *(*src)++;
	}
	if (**src == '"')
		(*src)++;
	return (dest);
}


static char	*copy_str_between_squotes(const char **src, char *dest)
{
	(*src)++;
	while (**src &&  **src != '\'')
		*dest++ = *(*src)++;
	if (**src == '\'')
		(*src)++;
	return (dest);
}

static char	*copy_backslash_escaped(const char **src, char *dest)
{
	(*src)++;
	if (**src && !is_word_delimiter(**src))
		*dest++ = *(*src)++;
	return (dest);
}

char	*extract_quoted_word(const char **input)
{
	char	*word;
	char	*dest;
	int		length;

	if (!input || !*input || is_word_delimiter(**input))
		return (NULL);
	length = calculate_word_length(*input);
	if (length == 0)
		return (NULL);
	word = malloc(length + 1);
	if (!word)
		return (MALLOC_FAILED);
	dest = word;
	while (**input && !is_word_delimiter(**input))
	{
		if (**input == '"')
			dest = copy_str_between_dquotes(input, dest);
		else if (**input == '\'')
			dest = copy_str_between_squotes(input, dest);
		else if (**input == '\\')
			dest = copy_backslash_escaped(input, dest);
		else
			*dest++ = *(*input)++;
	}
	*dest = '\0';
	return (word);
}
