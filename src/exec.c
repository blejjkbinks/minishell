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

int	ft_which_print(char **arg, char **env)
{
	char	*str;
	int		i;
	int		ret;

	ret = 0;
	i = 1;
	while (arg[i])
	{
		if (is_builtin(arg[i]))
			str = ft_strjoin(arg[i], ": minishell built-in command");
		else
			str = ft_which(arg[i], env);
		if (!str)
			ret = 1 + (0 * ft_printf("%s not found\n", arg[i]));
		if (str)
		{
			ft_printf("%s\n", str);
			free(str);
		}
		i++;
	}
	return (ret);
}

int	ft_export_magic(t_mshl *b, int x)
{
	if (x == 1 && ft_env_get(b->env, b->comm[0]))
		ft_env_set(b->env, b->comm[0], ft_strchr(b->comm[0], '=') + 1);
	else if (x == 1)
		b->env_extra = ft_export(b->env_extra, b->comm[0]);
	if (x == 0)
		b->env = ft_export(b->env, b->comm[1]);
	if (x == 0 && !ft_strchr(b->comm[1], '=') && ft_env_get(b->env_extra, b->comm[1]))
	{
		ft_env_set(b->env, b->comm[1], ft_env_get(b->env_extra, b->comm[1]));
		ft_unset(b->env_extra, b->comm[1]);
	}
	if (x == 2)
	{
		ft_unset(b->env, b->comm[1]);
		ft_unset(b->env_extra, b->comm[1]);
	}
	return (0);
}

int	exec_builtin(t_mshl *b)
{
	if (!ft_strncmp(b->comm[0], "echo", 10))
		return (ft_echo(b->comm));
	if (!ft_strncmp(b->comm[0], "cd", 10))
		return (ft_cd(b->comm, b->env));
	if (!ft_strncmp(b->comm[0], "pwd", 10))
		return (ft_pwd());
	if (!ft_strncmp(b->comm[0], "export", 10))
		return (ft_export_magic(b, 0));
	if (ft_strchr(b->comm[0], '='))
		return (ft_export_magic(b, 1));
	if (!ft_strncmp(b->comm[0], "unset", 10))
		return (ft_export_magic(b, 2));
	if (!ft_strncmp(b->comm[0], "env", 10))
		return (ft_env(b->env));
	//if (!ft_strncmp(b->comm[0], "env_extra", 10))
	//	return (ft_env(b->env_extra));
	if (!ft_strncmp(b->comm[0], "which", 10))
		return (ft_which_print(b->comm, b->env));
	if (!ft_strncmp(b->comm[0], "exit", 10))
		exit (0);// + (0 * ft_printf("byebye minishell\n")));
	return (-1);
}

int	exec_fork(char **arg, char **env)
{
	pid_t	pid;
	char	*str;
	int		status;

	pid = fork();
	if (pid < 0)
		return (4 + (0 * ft_printf("fork error\n")));
	else if (pid == 0)
	{
		str = ft_which(arg[0], env);
		//ft_printf("executing which command?:%s\n", str);
		if (!str)
			ft_printf("minishell: %s: command not found\n", arg[0]);
		else if (execve(str, arg, env))
			ft_printf("minishell: %s: is a directory (or a script?)\n", arg[0]);
		if (str)
			status = 126;
		else
			status = 127;
		if (str)
			free(str);
		exit (status);
	}
	else
	{
		waitpid(pid, &status, 0);
		return ((status & 0xff00) >> 8);
	}
}

/*int	exec_fork(t_mshl *b)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (4 + (0 * ft_printf("fork error\n")));
	else if (pid == 0)
	{
		if (is_builtin(b->comm[0]) || ft_strchr(b->comm[0], '='))
			exec_builtin(b);
		else
			exec_which(b->comm, b->env);
		return (-1);
	}
	else
	{
		waitpid(pid, &status, 0);
		return ((status & 0xff00) >> 8);
	}
}*/
