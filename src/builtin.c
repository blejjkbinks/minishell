/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 01:40:24 by rdomange          #+#    #+#             */
/*   Updated: 2024/09/28 01:40:25 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	char	**builtin;
	char	*s;
	int		i;

	//s = "echo,cd,pwd,export,unset,env,exit,which";
	s = "echo,cd,pwd,export,unset,env,exit,which,env_extra";
	builtin = ft_split(s, ",");
	i = -1;
	while (builtin[++i])
	{
		if (!ft_strncmp(str, builtin[i], ft_strlen(builtin[i]) + 1))
		{
			ft_split_free(builtin);
			return (1);
		}
	}
	ft_split_free(builtin);
	return (0);
}

char	*ft_which(char *arg, char **env)
{
	char	**path;
	char	*pwd;
	char	*ret;
	int		i;

	if (is_builtin(arg))
		return (NULL);
	if (!ft_strncmp(arg, "./", 2))
	{
		pwd = ft_getcwd();
		ret = ft_strjoin(pwd, arg + 1);
		free(pwd);
		if (!access(ret, X_OK))
			return (ret);
		else
			free(ret);
		return (NULL);
	}
	if (arg[0] == '/')
	{
		if (!access(arg, X_OK))
			return (ft_strdup(arg));
		return (NULL);
	}
	path = ft_split(ft_env_get(env, "PATH"), ":");
	i = 0;
	while (path[i])
	{
		pwd = ft_strjoin(path[i], "/");
		ret = ft_strjoin(pwd, arg);
		free(pwd);
		if (!access(ret, X_OK))
		{
			ft_split_free(path);
			return (ret);
		}
		free(ret);
		i++;
	}
	ft_split_free(path);
	return (NULL);
}

int	ft_echo(char **arg)
{
	int	i;
	int	nl;
	int	len;

	i = 1;
	nl = 1;
	len = ft_split_len(arg);
	if (len > 1 && !ft_strncmp(arg[1], "-n", 3))
	{
		nl = 0;
		i++;
	}
	while (i < len)
	{
		printf("%s", arg[i]);
		i++;
		if (i < len)
			printf(" ");
	}
	if (nl)
		printf("\n");
	return (0);
}
