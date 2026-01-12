/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 08:28:33 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/12 12:52:01 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "lexer.h"
# include "parser.h"
# include <unistd.h>

typedef struct	s_env
{
	char			*name;
	char			*value;
	int				exported;
	struct s_env	*next;
}	t_env;

// env_utils.c
char	*ft_strndup(const char *str, int len);
t_env	*env_find(t_env *env, const char *name);
char	*get_env(t_env *env, const char *name);
int		env_set(t_env **env, const char *name, const char *value, int exported);

// env_init.c
t_env	*env_new_node(const char *name, const char *value, int exported);
void	free_env(t_env **env);
void	env_add_back(t_env **env, t_env *new_node);
int		parse_env_line(const char *line, char **name, char **value);
t_env	*copy_new_env_from_env(char **env);
t_env	*init_env(char **env);

#endif
