/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:51:12 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/14 15:40:06 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdbool.h>

typedef struct s_brace_context
{
	char	*prefix;
	char	**elements;
	char	*suffix;
	int		element_count;
}	t_brace_context;

char	**expand_braces(const char *input);
void	free_string_array(char **array);

#endif
