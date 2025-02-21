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

//static void	ft_exec_which(char *comm, char **arg, char **env);

void ft_exec_pipe(char **pipes, char ***env, int *pidfd, int i)
{
    static int prev_fd = -1;  // holds the read end of the previous pipe
    int fds[2];
    pid_t pid;
    int is_last = (pipes[i + 1] == NULL);  // determine if this is the last command


    if (!is_last) 
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
    if (pid == 0) 
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
            close(fds[0]);  // Close the read end in the child.
            if (dup2(fds[1], STDOUT_FILENO) == -1) 
			{
                perror("dup2 fds[1]");
                exit(EXIT_FAILURE);
            }
            close(fds[1]);
        }
        char **args = ft_split_quotes(pipes[i], ' ');
		if (ft_isbuiltin(args[0]))
			ft_exec_builtin(args, env);
		else
		{
        	execve(args[0], args, *env);
        	perror("execve");
        	exit(EXIT_FAILURE);
		}
    }
	else 
	{
        pidfd[i] = pid;
        if (prev_fd != -1)
            close(prev_fd);
        if (!is_last) 
		{
            close(fds[1]);  // Parent doesn't write to this pipe.
            prev_fd = fds[0];
        } 
		else
            prev_fd = -1;
    }
}

/*void	ft_exec_pipe(char **comm, char ***env, pid_t *pid)	//fdr[4]
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
}*/
