/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:40:03 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/07 20:44:27 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_special_char(char c)
{
	return (c == '"' || c == '\'' || c == '\\' || c == '$' || c == '~');
}

t_token	*handle_special(const char **input)
{
	if ((*input)[0] == '"')
		return ((*input)++, new_token(DQUOTE, "\""));
	if ((*input)[0] == '\'')
		return ((*input)++, new_token(SQUOTE, "'"));
	if ((*input)[0] == '\\')
		return ((*input)++, new_token(BACKSLASH, "\\"));
	if ((*input)[0] == '$')
		return ((*input)++, new_token(DOLLAR, "$"));
	if ((*input)[0] == '~')
		return ((*input)++, new_token(TILDE, "~"));

	return (NULL);
}

t_token	*handle_word(const char **input)
{
	const char	*start;
	int			len;
	char		*word;
	t_token		*token;

	start = *input;
	len = 0;
	while (start[len] && !is_whitespace(start[len]) && !is_operator_char(start[len]) && !is_special_char(start[len]))
		len++;
	if (len == 0)
		return (NULL);
	word = malloc(len + 1);
	if (!word)
		return (MALLOC_FAILED);
	strncpy(word, start, len);
	word[len] = '\0';
	token = new_token(WORD, word);
	free(word);
	*input += len;
	return (token);
}

t_token	*get_next_token(const char **input)
{
	t_token	*token;

	while (is_whitespace(**input))
		(*input)++;
	if (!**input)
		return (NULL);
	token = handle_double_operator(input);
	if (token)
		return (token);
	if (is_operator_char(**input))
		return (handle_sigle_operator(input));
	if (is_special_char(**input))
		return (handle_special(input));
	return (handle_word(input));
}

t_token	*lexer_tokenizer(const char *input)
{
	t_token	*head;
	t_token	*token;

	head = NULL;
	while (*input)
	{
		token = get_next_token(&input);
		if (!token)
		{
			token_free(head);
			return (NULL);
		}
		if (token)
			token_add_back(&head, token);
	}
	return (head);
}
