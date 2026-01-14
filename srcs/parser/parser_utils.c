/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:47:49 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/12 07:49:16 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

bool	is_redir(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_APPEND || type == REDIR_HEREDOC
		|| type == REDIR_FD_IN || type == REDIR_FD_OUT);
}

t_token	*get_current_token(t_token *token)
{
	return (token);
}

t_token	*get_token_and_advance(t_token **token)
{
	t_token	*current;

	if (!token || !*token)
		return (NULL);
	current = *token;
	*token = (*token)->next;
	return (current);
}

bool	match_token(t_token **token, t_token_type type)
{
	t_token	*current;

	current = get_current_token(*token);
	if (!current || current->type != type)
		return (false);
	get_token_and_advance(token);
	return(true);
}		
