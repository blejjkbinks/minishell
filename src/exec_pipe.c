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

static void	setup_redirection(int is_last, int prev_fd, int *fds)
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 prev_fd");
			exit(EXIT_FAILURE);
		}
		close(prev_fd);
	}
	if (!is_last)
	{
		close(fds[0]);
		if (dup2(fds[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 fds[1]");
			exit(EXIT_FAILURE);
		}
		close(fds[1]);
	}
}

static void	child_process(char *cmd, char ***env)
{
	char	**args;
	char	*path;

	args = ft_split_quotes(cmd, ' ');
	if (ft_isbuiltin(args[0]))
	{
		ft_exec_builtin(args, env);
		ft_split_free(args);
	}
	else
	{
		path = ft_which(args[0], *env);
		if (!path)
		{
			printf("%s: command not found\n", args[0]);
			return ;
		}
		execve(path, args, *env);
		free(path);
		ft_split_free(args);
		exit(EXIT_FAILURE);
	}
}

static pid_t	create_child(char **pipes, int i, int *fds, int *is_last)
{
	pid_t	pid;

	*is_last = (pipes[i + 1] == NULL);
	if (!(*is_last))
	{
		if (pipe(fds) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

static void	parent_process(int *fds, int is_last, int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (! is_last)
	{
		close(fds[1]);
		*prev_fd = fds[0];
	}
	else
		*prev_fd = -1;
}

void	ft_exec_pipe(char **pipe, char ***env, int *pidfd, int i)
{
	static int	prev_fd;
	static int	first_time;
	int			fds[2];
	int			is_last;
	pid_t		pid;

	if (first_time != 1)
	{
		prev_fd = -1;
		first_time = 1;
	}
	pid = create_child(pipe, i, fds, &is_last);
	if (pid == 0)
	{
		setup_redirection(is_last, prev_fd, fds);
		child_process(pipe[i], env);
	}
	else
	{
		pidfd[i] = pid;
		parent_process(fds, is_last, &prev_fd);
	}
}
