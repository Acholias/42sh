/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 08:31:33 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/12 09:51:04 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

char	*ft_strndup(const char *str, int len)
{
	char	*dup;
	int		index;

	index = 0;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (index < len)
	{
		dup[index] = str[index];
		index++;
	}
	dup[index] = '\0';
	return (dup);
}

t_env	*env_new_node(const char *name, const char *value, int exported)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (MALLOC_FAILED);
	node->name = strdup(name);
	node->value = strdup(value ? value : "");
	if (!node->name || !node->value)
	{
		free(node->name);
		free(node->value);
		free(node);
		return (NULL);
	}
	node->exported = exported;
	node->next = NULL;
	return (node);
}

void	free_env(t_env **env)
{
	t_env	*current;
	t_env	*next;

	if (!env || !*env)
		return ;
	current = *env;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	*env = NULL;
}

void	env_add_back(t_env **env, t_env *new_node)
{
	t_env	*current;

	if (!new_node)
		return ;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

int	parse_env_line(const char *line, char **name, char **value)
{
	char	*equal;

	equal = strchr(line, '=');
	if (!equal)
		return (-1);
	*name = ft_strndup(line, equal - line);
	if (!*name)
		return (-1);
	*value = strdup(equal + 1);
	if (!*value)
	{
		free(*value);
		return (-1);
	}
	return (0);
}

t_env	*copy_new_env_from_env(char **env)
{
	t_env	*new_env;
	t_env	*new_node;
	char	*name;
	char	*value;
	size_t	index;

	if (!env)
		return (NULL);
	new_env = NULL;
	index = 0;
	while (env[index])
	{
		if (parse_env_line(env[index], &name, &value) == 0)
		{
			new_node = env_new_node(name, value, 1);
			free(name);
			free(value);
			if (!new_node)
			{
				free_env(&new_env);
				return (NULL);
			}
			env_add_back(&new_env, new_node);
		}
		index++;
	}
	return (new_env);
}

static int	add_default_var(t_env **env, const char *name, const char *value)
{
	t_env	*new;

	new = env_new_node(name, value, 1);
	if (!new)
		return (-1);
	env_add_back(env, new);
	return (0);
}

static t_env	*create_env_backup(void)
{
	t_env	*env;
	char	cwd[1024];

	env = NULL;
	if (getcwd(cwd, sizeof(cwd)))
		add_default_var(&env, "PWD", cwd);
	else
		add_default_var(&env, "PWD", "/");
	add_default_var(&env, "NIX_PROFILES", "/nix/var/nix/profiles/default /.nix-profile");
	add_default_var(&env, "NIX_SSL_CERT_FILE", "/etc/ssl/certs/ca-certificates.crt");
	add_default_var(&env, "XDG_DATA_DIRS", "/usr/local/share:/usr/share:/.nix-profile/share:/nix/var/nix/profiles/default/share");
	add_default_var(&env, "PATH", "/zig-linux-x86_64-0.13.0:/.nix-profile/bin:/nix/var/nix/profiles/default/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	add_default_var(&env, "_", "/usr/bin/env");
	return (env);
}

t_env	*init_env(char **env)
{
	t_env	*new_env;

	if (env && env[0])
		new_env = copy_new_env_from_env(env);
	else
		new_env = create_env_backup();
	return (new_env);
}
