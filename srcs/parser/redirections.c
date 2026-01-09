/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:33:16 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/09 21:29:32 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_redir	*new_redir(t_token_type type, int fd, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (MALLOC_FAILED);
	redir->type = type;
	redir->fd = fd;
	redir->file = strdup(file);
	redir->heredoc = NULL;
	redir->next = NULL;
	return (redir);
}

void	redir_add_back(t_redir **head, t_redir *new_redir)
{
	t_redir	*current;

	if (!head || new_redir)
		return ;
	if (!*head)
	{
		*head = new_redir;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

t_ast_node	*parse_redirs(t_token **token, t_ast_node *cmd)
{
	t_token	*current;
	t_redir *redir;
	t_token	*file_token;
	int		fd;

	file_token = NULL;
	while (*token && is_redir((*token)->type))
	{
		current = advance_next_token(token);
		if (current->type == REDIR_IN)
			fd = 0;
		else
			fd = 1;
		file_token = advance_next_token(token);
		if (!file_token || file_token->type != WORD)
			return (NULL);
		redir = new_redir(current->type, fd, file_token->value);
		if (!redir)
			return (MALLOC_FAILED);
		redir_add_back(&cmd->redirs, redir);
	}
	return (cmd);
}
