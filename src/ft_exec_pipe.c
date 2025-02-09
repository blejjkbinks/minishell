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

/*
redirs and pipes happen here
int fd_in for redir in, -1 if no redirs happen
int fd_out for out, same
int mode_in for read/heredoc
int mode_out for append/overwrite
*/

void	ft_exec_pipe(char **comm, char ***env, pid_t *pid)
{
	*pid = fork();
	if (*pid == 0)
	{
		//ready pipes and redirs
		if (ft_isbuiltin(comm[0]))
			exit(ft_exec_builtin(comm, env));
		ft_exec_which(comm[0], comm, env[0]);
		//close pipes and redirs
	}
}

static void	ft_exec_which(char *comm, char **arg, char **env)
{
	char	*path;
	char	**bash;

	path = ft_which(comm, env);
	bash = ft_env_dup(arg);
	ft_memmove(bash + 1, bash, ft_split_len(bash) * sizeof(char *));
	bash[0] = "/bin/bash";
	if (!path && !access(comm, R_OK))
		ft_printf("minishell: %s: is a directory\n", comm);
	else if (!path)
		ft_printf("minishell: %s: command not found\n", comm);
	else if (execve(path, arg, env) && execve(bash[0], bash, env))
		ft_printf("minishell: %s: permission denied\n", comm);
	exit (126 + (path != NULL));
}
