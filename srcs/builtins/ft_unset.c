/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:28:41 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/16 17:34:01 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static bool	is_valid_identifier(const char *name)
{
	int index;

	if (!name || !name[0])
		return (false);
	if (ft_isalpha(name[0]) && name[0] != '_')
		return (false);
	index = 1;
	while (name[index])
	{
		if (!ft_isalpha(name[index]) && name[index] != '_')
			return (false);
		index++;
	}
	return (true);
}

static int	env_unset(t_env **env, const char *name)
{
	t_env	*current;
	t_env	*prev;

	if (!env || !*env || !name)
		return (1);
	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

int	ft_unset(char **argv, t_env **env)
{
	int	index;
	int	ret;

	if (!argv[1])
		return (0);
	ret = 0;
	index = 1;
	while (argv[index])
	{
		if (!is_valid_identifier(argv[index]))
		{
			fprintf(stderr, "\runset: `%s': not a valid identifier\n", argv[index]);
			ret = 1;
		}
		else
			env_unset(env, argv[index]);
		index++;
	}
	return (ret);
}
