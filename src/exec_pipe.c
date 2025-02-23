/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:35:56 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/10 18:46:18 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_which(char *comm, char **arg, char **env);
static void	ready_pipe(int *pidfd, int *fdp, int i);
static void	close_pipe(int *pidfd, int *fdp, int i);

void	ft_exec_pipe(char **comm, char ***env, int *pidfd, int i)
{
	char	**arg;
	int		fdp[2];

	if (comm[i + 1])
	{
		pipe(fdp);
		pidfd[(N * i) + 3] = fdp[0];
		if (MS_DEBUG && ft_printf("MS_DEBUG: PIPE(): "))
			ft_printf("fdp[0]:'%d', fdp[1]:'%d'\n", fdp[0], fdp[1]);
	}
	else
	{
		fdp[0] = -1;
		fdp[1] = -1;
	}
	pidfd[N * i] = fork();
	if (pidfd[N * i] == 0)
	{
		arg = ft_split_quotes(comm[i], ' ');
		ft_splittrim_quotes(arg);
		ft_strtolower(arg[0]);
		ft_split_debug(arg, "EXEC");
//
		ready_pipe(pidfd, fdp, i);
//
		if (ft_isbuiltin(arg[0]))
			exit(ft_exec_builtin(arg, env));
		ft_exec_which(arg[0], arg, env[0]);
	}
	close_pipe(pidfd, fdp, i);
}

static void	ready_pipe(int *pidfd, int *fdp, int i)
{
	if (pidfd[(N * i) + 1])
	{
		ft_dup_debug(pidfd[(N * i) + 1], STDIN_FILENO, "INPUT");
		dup2(pidfd[(N * i) + 1], STDIN_FILENO);
		close(pidfd[(N * i) + 1]);
	}
	else if (i && pidfd[(N * (i - 1)) + 3] != -1)
	{
		ft_dup_debug(pidfd[(N * (i - 1)) + 3], STDIN_FILENO, "PREV PIPE");
		dup2(pidfd[(N * (i - 1)) + 3], STDIN_FILENO);
		close(pidfd[(N * (i - 1)) + 3]);
	}
	if (pidfd[(N * i) + 2])
	{
		ft_dup_debug(pidfd[(N * i) + 2], STDOUT_FILENO, "OUTPUT");
		dup2(pidfd[(N * i) + 2], STDOUT_FILENO);
		close(pidfd[(N * i) + 2]);
	}
	else if (fdp[1] != -1)
	{
		ft_dup_debug(fdp[1], STDOUT_FILENO, "NEXT PIPE");
		dup2(fdp[1], STDOUT_FILENO);
		close(fdp[1]);
	}
	close_pipe(pidfd, fdp, i);
}

static void	close_pipe(int *pidfd, int *fdp, int i)
{
	if (i && pidfd[(N * (i - 1)) + 3] != -1)
	{
		close(pidfd[(N * (i - 1)) + 3]);
		pidfd[(N * (i - 1)) + 3] = -1;
	}
	if (fdp[1] != -1)
	{
		close(fdp[1]);
		fdp[1] = -1;
	}
}

static void	ft_exec_which(char *comm, char **arg, char **env)
{
	char	*path;
	char	**bash;

	path = ft_which(comm, env);
	if (MS_DEBUG)
		ft_printf("MS_DEBUG: WHICH: '%s'\n", path);
	bash = ft_env_dup(arg);
	ft_memmove(bash + 1, bash, ft_split_len(bash) * sizeof(char *));
	bash[0] = "/bin/bash";
	if (!path && opendir(comm))
		ft_printf("minishell: %s: is a directory\n", comm);
	else if (!path && ft_strchr(comm, '/') && access(comm, F_OK))
		ft_printf("minishell: %s: no such file or directory\n", comm);
	else if (!path && access(comm, F_OK))
		ft_printf("minishell: %s: command not found\n", comm);
	else if (execve(path, arg, env))// && execve(bash[0], bash, env))
		ft_printf("minishell: %s: permission denied\n", comm);
	exit (126 + (path != NULL));
}

int	invalid_pipe(char *input)
{
	while (*input)
	{
		if (*input == '|')
		{
			input++;
			while (*input && ft_isspace(*input))
				input++;
			if (*input == '\0')
			{
				printf("Pipe '|' must be followed by a command\n");
				return (1);
			}
		}
		else
			input++;
	}
	return (0);
}
