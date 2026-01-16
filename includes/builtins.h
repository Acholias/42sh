/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:00:23 by lumugot           #+#    #+#             */
/*   Updated: 2026/01/16 13:39:54 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "env.h"
# include <stdbool.h>

bool	is_builtin(const char *cmd);
int		ft_echo(char **argv);
int		ft_pwd(void);
int		ft_exit(char **argv, int last_exit_code);
int		ft_env(	t_env *env);
int		ft_cd(char **argv, t_env *env);
int		ft_export(char **argv, t_env *env);
int		ft_unset(char **argv, t_env *env);
int		execute_builtins(char **argv, t_env *env);

#endif
