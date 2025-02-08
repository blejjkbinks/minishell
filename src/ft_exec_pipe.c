/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:35:56 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/08 18:35:59 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_which(char *comm, char **arg, char **env);
static int	ft_exec_bash(char **arg, char **env);

void	ft_exec_pipe(char **comm, char ***env, pid_t *pid)
{
	*pid = fork();
	if (*pid == 0)
	{
		//ready pipes and redirs
		if (ft_isbuiltin(comm[0]))
			exit(ft_exec_builtin(comm, env));
		ft_exec_which(comm[0], comm, env[0]);
	}
}

static void	ft_exec_which(char *comm, char **arg, char **env)
{
	char	*path;

	path = ft_which(comm, env);
	if (!path && !access(comm, R_OK))
	ft_printf("minishell: %s: is a directory\n", comm);
	else if (!path)
		ft_printf("minishell: %s: command not found\n", comm);
	else if (execve(path, arg, env) && ft_exec_bash(arg, env))
		ft_printf("minishell: %s: permission denied\n", comm);
	exit (126 + (path != NULL));
}

static int	ft_exec_bash(char **arg, char **env)
{
	char	**tmp;
	int		len;

	tmp = ft_env_dup(arg);
	len = ft_split_len(arg);
	ft_memmove(tmp + 1, tmp, len * sizeof(char *));
	tmp[0] = "/bin/bash";
	return (execve(tmp[0], tmp, env));
}
