/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 08:30:51 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/12 10:24:03 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

t_env	*env_find(t_env *env, const char *name)
{
	while (env)
	{
		if (strcmp(env->name, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*get_env(t_env *env, const char *name)
{
	t_env	*node;

	node = env_find(env, name);
	if (node)
		return (node->value);
	return (NULL);
}

int	env_set(t_env **env, const char *name, const char *value, int exported)
{
	t_env	*node;
	t_env	*new;
	char	*new_value;

	node = env_find(*env, name);
	if (node)
	{
		new_value = strdup(value ? value : "");
		if (!new_value)
			return (-1);
		free(node->value);
		node->value = new_value;
		if (exported)
			node->exported = 1;
	}
	new = env_new_node(name, value, exported);
	if (!new)
		return (-1);
	new->next = *env;
	*env = new;
	return (0);
}
