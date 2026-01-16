/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:40:07 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/16 17:33:08 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	ft_env(t_env *env)
{
	t_env *current;

	if (!env)
		return (1);
	current = env;
	while (current)
	{
		if (current->exported && current->value)
			printf("\r%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (0);
}
