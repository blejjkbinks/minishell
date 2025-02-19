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

/*void execute_pipes(char ***commands, char ***env)
{
	int		i;
	int		num_cmd;
	int		pipefd[2];
	int		in_fd;
	pid_t	pid;

	num_cmd = ft_count_cmds(commands); //make command
	i = 0;
	in_fd = 0;
	while (i < num_cmd)
	{
		if (i < num_cmd - 1)
			pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			if (i != 0)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (i < num_cmd - 1)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
				close(pipefd[2]);
			}
			if (ft_isbuiltin(commands[i][0]))
				exit(ft_exec_builtin(commands[i]));
			ft_exec_which(commands[i][0], commands[i], env[0]);
			exit(EXIT_FAILURE);
		}
		if (i != 0)
			close(in_fd);
		if (i < num_cmd - 1)
		{
			close(pipefd[1]);
			in_fd = pipefd[0];
		}
	}
	i = 0;
	while (i < num_cmd)
	{
		wait(NULL);
		i++;
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
	{
		ft_printf("minishell: %s: is a directory\n", comm);
		exit(126);
	}
	else if (!path)
	{
		ft_printf("minishell: %s: command not found\n", comm);
		exit(127);
	}
	else if (execve(path, arg, env) == -1)
	{
		ft_printf("minishell: %s: permission denied\n", comm);
		exit(126);
	}
}*/

void	ft_exec_pipe(char **comm, char ***env, pid_t *pid)	//fdr[4]
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
