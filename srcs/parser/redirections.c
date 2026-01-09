/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:33:16 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/09 19:38:08 by lumugot          ###   ########.fr       */
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

}
