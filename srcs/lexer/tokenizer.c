/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:40:03 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/14 15:42:53 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

t_token	*handle_word(const char **input)
{
	char		*word;
	t_token		*token;
	char		**expanded;
	int			i;

	word = extract_quoted_word(input);
	if (!word)
		return (MALLOC_FAILED);
	expanded = expand_braces(word);
	free(word);
	if (!expanded || !expanded[0])
		return (NULL);
	token = new_token(WORD, expanded[0]);
	if (expanded[1])
	{
		i = 1;
		while (expanded[i])
		{
			token_add_back(&token, new_token(WORD, expanded[i]));
			i++;
		}
	}
	free_string_array(expanded);
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

static	t_token	*tokenize_single_input(const char *input)
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

void	token_append(t_token **head, t_token *to_add)
{
	t_token	*current;

	if (!head || !to_add)
		return ;
	if (!*head)
	{
		*head = to_add;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = to_add;
}

t_token	*lexer_tokenizer(const char *input)
{
	if (!input || !*input)
		return (NULL);
	return (tokenize_single_input(input));
}
