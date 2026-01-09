/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 21:21:01 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/09 21:25:00 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_ast_node	*parser_build_ast(t_token *token)
{
	t_ast_node	*ast;

	if (!token)
		return (NULL);
	ast = parse_complete_command(&token);
	if (!ast)
	{
		fprintf(stderr, "\rSyntex error\n");
		return (NULL);
	}
	if (token)
	{
		fprintf(stderr, "\rSyntax error: unexpected token\n");
		free_ast(ast);
		return (NULL);
	}
	return (ast);
}
