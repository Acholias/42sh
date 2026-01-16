/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:38:17 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/16 15:08:44 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static bool	is_valid_identifier(const char *name)
{
	int	index;

	if (!name || !name[0])
		return (false);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (false);
	index = 1;
	while (name[index])
	{
		if (!ft_isalnum(name[index]) && name[index] != '_')
			return (false);
		index++;
	}
	return (true);
}

static void	print_export_vars(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (current->exported)
		{
			printf("declare -x %s", current->name);
			if (current->value)
				printf("=\"%s\"", current->value);
			printf("\n");
		}
		current = current->next;
	}
}

static int	parse_assignment(char *arg, char **name, char **value, bool *append)
{
	char	*pos;
	int		index;

	*append = false;
	*value = NULL;
	pos = ft_strchr(arg, '=');
	if (!pos)
	{
		*name = arg;
		return (0);
	}
	if (pos > arg && *(pos -1) == '+')
	{
		*append = true;
		*(pos - 1) = '\0';
	}
	else
		*pos = '\0';
	*name = arg;
	*value = pos + 1;
	return (0);
}

static int	handle_append(t_env **env, const char *name, const char *new_value)
{
	t_env	*var;
	char	*concate;
	size_t	old_len;
	size_t	new_len;

	var = env_find(*env, name);
	if (!var || !var->value)
		return (env_set(env, name, new_value, 1));
	old_len = ft_strlen(var->value);
	new_len = ft_strlen(new_value);
	concate = malloc(old_len + new_len + 1);
	if (!concate)
		return (1);
	ft_strcpy(concate, var->value);
	ft_strcat(concate, new_value);
	env_set(env, name, concate, 1);
	free(concate);
	return (0);

}

int	ft_export(char **argv, t_env **env)
{
	int		index;
	char	*name;
	char	*value;
	bool	append;
	int		ret;
	t_env	*var;

	if (!argv[1])
	{
		print_export_vars(*env);
		return (0);
	}
	ret = 0;
	index = 0;
	while (argv[index])
	{
		parse_assignment(argv[index], &name, &value, &append);
		if (!is_valid_identifier(name))
		{
			fprintf(stderr, "export: `%s: not a valid identifier\n", argv[index]);
			ret = 1;
			index++;
			continue;
		}
		if (value)
		{
			if (append)
				handle_append(env, name, value);
			else
				env_set(env, name, value, 1);
		}
		else
		{
			var = env_find(*env, name);
			if (var)
				var->exported = 1;
			else
				env_set(env, name, "", 1);
		}
		index++;
	}
	return (ret);
}
