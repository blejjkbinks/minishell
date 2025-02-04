/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:27:25 by rdomange          #+#    #+#             */
/*   Updated: 2024/09/29 11:27:52 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_bash_script(char **arg, char **env)
{
	char	**tmp;
	int		i;

	tmp = ft_env_dup(arg);
	i = ft_split_len(arg);
	while (i > 0)
	{
		tmp[i] = tmp[i - 1];
		i--;
	}
	tmp[0] = "/bin/bash";
	return (execve(tmp[0], tmp, env));
}

int	ft_exec_which(char **arg, char **env)
{
	char	*str;

	str = ft_which(arg[0], env);
	if (!str && !access(arg[0], R_OK))
		ft_printf("minishell: %s: is a directory\n", arg[0]);
	else if (!str)
		ft_printf("minishell: %s: command not found\n", arg[0]);
	else if (execve(str, arg, env) && ft_exec_bash_script(arg, env))
		ft_printf("minishell: %s: permission denied\n", arg[0]);
	exit (126 + (str != NULL));
}

void	ft_exec_pipe_segment_norm(t_mshl *m)
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
}

void	ft_exec_pipesegment(t_mshl *m)
{
	m->pids[m->i] = fork();
	if (m->pids[m->i] == 0)
	{
		if (is_builtin(m->comm[0]))
			exit(ft_exec_builtin(m));
		ft_exec_which(m->comm, m->env);
		exit(6 + (0 * ft_printf("exec_pipesegment %d failed\n", m->i)));
	}
}
