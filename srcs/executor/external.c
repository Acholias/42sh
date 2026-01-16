/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:15:19 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/16 18:51:50 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

char	**env_to_array(t_env *env)
{
	char	**array;
	t_env	*current;
	int		count;
	int		index;
	char	*temp;

	count = 0;
	current = env;
	while (current && ++count)
		current = current->next;
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (MALLOC_FAILED);
	index = 0;
	current = env;
	while (current)
	{
		temp = malloc(ft_strlen(current->name) + ft_strlen(current->value) + 3);
		if (!temp)
		{
			while (index > 0)
				free(array[--index]);
			free(array);
			return (MALLOC_FAILED);
		}
		sprintf(temp, "\r%s=%s", current->name, current->value);
		array[index++] = temp;
		current = current->next;
	}
	array[index] = NULL;
	return (array);
}

static char	*extract_path_dir(const char *path, int *index)
{
	int		start;
	int		len;
	char	*dir;

	start = *index;
	len = 0;
	while (path[*index] && path[*index] != ':')
	{
		(*index)++;
		len++;
	}
	if (len == 0)
		return (NULL);
	dir = malloc(len + 1);
	if (!dir)
		return (MALLOC_FAILED);
	ft_strncpy(dir, path + start, len);
	dir[len] = '\0';
	if (path[*index] == ':')
		(*index)++;
	return (dir);
}

char	*find_command_path(const char *cmd, t_env *env)
{
	char	*path_env;
	char	*dir;
	char	full_path[4096];
	int		index;

	if (ft_strchr(cmd, '/'))
		return (access(cmd, X_OK) == 0 ? ft_strdup(cmd) : NULL);
	path_env = get_env(env, "PATH");
	if (!path_env)
		return (NULL);
	index = 0;
	while (path_env[index])
	{
		dir = extract_path_dir(path_env, &index);
		if (!dir)
			break ;
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
		free(dir);
		if (access(full_path, X_OK) == 0)
			return (ft_strdup(full_path));
	}
	return (NULL);
}

int	execute_external(t_simple_cmd *cmd, t_exec_ctx *ctx)
{
	pid_t	pid;
	int		status;
	int		index;
	char	*cmd_path;
	char	**envp;

	cmd_path = find_command_path(cmd->argv[0], *ctx->env);
	if (!cmd_path)
	{
		fprintf(stderr, "\r42sh: %s: command not found\n", cmd->argv[0]);
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return (1);
	}
	if (pid == 0)
	{
		envp = env_to_array(*ctx->env);
		if (!envp)
			exit(1);
		execve(cmd_path, cmd->argv, envp);
		perror("execve");
		free(cmd_path);
		index = 0;
		while (envp[index])
			free(envp[index++]);
		free(envp);
		exit(127);
	}
	free(cmd_path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
