/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:43:55 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/16 14:10:23 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static char	*get_target_dir(char **argv, t_env *env)
{
	char	*target;

	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
	{
		target = get_env(env, "HOME");
		if (!target)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (NULL);
		}
		return (target);
	}
	if (ft_strcmp(argv[1], "-") == 0)
	{
		target = get_env(env, "OLDPWD");
		if (!target)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return (NULL);
		}
		return (target);
	}
	return (argv[1]);
}

static void	update_pwd_var(t_env **env, const char *oldpwd)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
	{
		env_set(env, "PWD", cwd, 1);
		if (oldpwd)
			env_set(env, "OLDPWD", cwd, 1);
	}
}

int	ft_cd(char **argv, t_env **env)
{
	char	*target;
	char	oldpwd[4096];

	if (argv[1] && argv[2])
	{
		fprintf(stderr, "cd: too many arguments\n");
		return (1);
	}
	if (!getcwd(oldpwd, sizeof(oldpwd)))
		oldpwd[0] = '\0';
	target = get_target_dir(argv, *env);
	if (!target)
		return (1);
	if (chdir(target) == 1)
	{
		perror("cd");
		return (1);
	}
	update_pwd_var(env, oldpwd);
	return (0);
}
