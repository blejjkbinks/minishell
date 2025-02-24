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

/*
redirs and pipes happen here
int fd_in for redir in, -1 if no redirs happen
int fd_out for out, same
int mode_in for read/heredoc
int mode_out for append/overwrite
*/

//void	ft_exec_pipe(char **comm, char ***env, pid_t *pid)	//fdr[4]
/*
void	ft_exec_pipe(char **comm, char ***env, int *pidfd, int i)
{
	char	**arg;

	pidfd[3 * i] = fork();
	if (pidfd[3 * i] == 0)
	{
		arg = ft_split_quotes(comm[i], ' ');
		ft_splittrim_quotes(arg);
		ft_strtolower(arg[0]);
		ft_split_debug(arg, "EXEC");
		//ready pipes and redirs
		//redir_in_fd = pidfd[(3 * i) + 1];
		//redir_out_fd = pidfd[(3 * i) + 2];
		if (ft_isbuiltin(arg[0]))
			exit(ft_exec_builtin(arg, env));
		ft_exec_which(arg[0], arg, env[0]);
		//close pipes and redirs
	}
}
*/

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
	if (fdp[0] != -1)
		close(fdp[0]);
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

//
//
//

/*

void ft_ready_pipe(t_mshl *m)
{
	m->comm = m->triple[m->i];
	ft_strtolower(m->comm[0]);
	m->is_first = (m->i == 0);
	m->is_last = (m->triple[m->i + 1] == NULL);
	if (!m->is_last && pipe(m->pipefd) < 0)
		exit(5 + (0 * ft_printf("pipe failed\n")));
	if (m->fd_in != -1 && m->is_first)
		m->prevfd = m->fd_in;
	if (m->fd_out != -1 && m->is_last)
		m->pipefd[1] = m->fd_out;
}

int ft_exec_pipesegment(t_mshl *m)
{
	int status;

	m->pid = fork();
	if (m->pid == 0)
	{
		if (m->fd_in != -1)
		{
			dup2(m->fd_in, STDIN_FILENO);
			close(m->fd_in);
		}
		else if (m->prevfd != STDIN_FILENO)
		{
			dup2(m->prevfd, STDIN_FILENO);
			close(m->prevfd);
		}
		if (m->fd_out != -1 && m->is_last)
		{
			dup2(m->fd_out, STDOUT_FILENO);
			close(m->fd_out);
		}
		else if (!m->is_last)
		{
			dup2(m->pipefd[1], STDOUT_FILENO);
			close(m->pipefd[1]);
		}
		close(m->pipefd[0]);

		if (is_builtin(m->comm[0]))
			exit(ft_exec_builtin(m));

		ft_exec_which(&status, m->comm, m->env);
		exit(6 + (0 * ft_printf("exec_pipesegment %d failed\n", m->i)));
	}
	m->pids[m->i] = m->pid;
	return (m->pid);
}

void ft_cleanup_pipe(t_mshl *m)
{
	if (m->prevfd != STDIN_FILENO)
		close(m->prevfd);
	if (!m->is_last)
		close(m->pipefd[1]);
	if (m->is_last)
		m->prevfd = STDIN_FILENO;
	else
		m->prevfd = m->pipefd[0];
}

FUNCTION ft_exec_pipe(commands, env, pidfd, i)
    comm = split command[i] by spaces while handling quotes
    remove extra quotes from comm

    CREATE a child process (fork)
    IF fork failed
        PRINT error and exit

    IF child process (fork returns 0)
        IF not first command
            REDIRECT stdin to read from the previous pipe

        IF not last command
            REDIRECT stdout to write to the next pipe

        CLOSE all unnecessary pipes

        IF command is a builtin
            EXECUTE builtin and exit

        EXECUTE command using path lookup
        IF execution fails
            PRINT error and exit with status 127

    ELSE (parent process)
        IF not first command
            CLOSE read end of the previous pipe
        IF not last command
            CLOSE write end of the current pipe
END FUNCTION

*/