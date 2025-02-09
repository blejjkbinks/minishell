/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:58:24 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/06 17:14:06 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_which_path(char *arg, char **env, char *pwd, char *ret);

//s = "cd,export,unset,exit";
//s = "echo,pwd,env,which,cd,export,unset,env_extra,alias,unalias,source,exit";
//s = "echo,pwd,env,which,cd,export,unset,env_extra,alias,unalias,source,exit";

int	ft_isbuiltin(char *str)
{
	char	**builtin;
	char	*s;
	int		i;

	if (ft_strchr(str, '=') && ft_env_namelen(str))
		return (3);
//	s = "echo,pwd,env,which,cd,export,unset,alias,unalias,source,exit";
//s = "echo,pwd,env,which,cd,export,unset,env_extra,alias,unalias,source,exit";
	builtin = ft_split(s, ',');
	i = 0;
	while (builtin[i])
	{
		if (!ft_strcmp(str, builtin[i]))
		{
			ft_split_free(builtin);
			if (i >= 4)
				return (2);
			return (1);
		}
		i++;
	}
	ft_split_free(builtin);
	return (0);
}

char	*ft_which(char *arg, char **env)
{
	char	*pwd;
	char	*ret;

	pwd = NULL;
	ret = NULL;
	if (ft_isbuiltin(arg))
		return (NULL);
	if (!ft_strncmp(arg, "./", 2))
	{
		pwd = ft_getcwd();
		ret = ft_strjoin(pwd, arg + 1);
		free(pwd);
		if (!access(ret, X_OK))
			return (ret);
		free(ret);
		return (NULL);
	}
	if (arg[0] == '/')
	{
		if (!access(arg, X_OK))
			return (ft_strdup(arg));
		return (NULL);
	}
	return (ft_which_path(arg, env, pwd, ret));
}

static char	*ft_which_path(char *arg, char **env, char *pwd, char *ret)
{
	char	**path;
	int		i;

	path = ft_split(ft_env_get(env, "PATH"), ':');
	i = 0;
	while (path && path[i])
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
