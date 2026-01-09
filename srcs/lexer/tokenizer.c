/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:40:03 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/08 19:30:59 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

t_token	*handle_word(const char **input)
{
	char		*word;
	t_token		*token;

	word = extract_quoted_word(input);
	if (!word)
		return (MALLOC_FAILED);
	token = new_token(WORD, word);
	free(word);
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
	return (handle_word(input));
}

t_token	*lexer_tokenizer(const char *input)
{
	t_token	*head;
	t_token	*token;

	head = NULL;
	if (!check_quotes_closed(input))
		return (NULL);
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
