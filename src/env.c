/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:33:52 by rdomange          #+#    #+#             */
/*   Updated: 2024/09/19 20:33:54 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_env_dup(char **env)
{
	char	**ret;
	int		i;

	ret = (char **)ft_malloc((ft_split_len(env) + 1) * sizeof(char *));
	i = 0;
	while (env[i])
	{
		ret[i] = ft_strdup(env[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

char	*ft_env_name(char *name)
{
	char	*ret;
	int		i;

	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (NULL);
	i = 0;
	ret = ft_strdup(name);
	while (ft_isalnum(name[i]) || name[i] == '_')
		i++;
	ret[i] = 0;
	return (ret);
}

char	*ft_env_get(char **env, char *name)
{
	int	i;
	int	len;

	name = ft_env_name(name);
	if (!name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
		{
			free(name);
			return (&(env[i][len + 1]));
		}
		i++;
	}
	free(name);
	return ("");
}

int	ft_env_set(char **env, char *name, char *val)
{
	int		i;
	int		len;
	char	*str;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
		{
			free(env[i]);
			str = ft_strjoin(name, "=");
			env[i] = ft_strjoin(str, val);
			free(str);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**ft_export(char **env, char *arg)
{
	char	**ret;
	char	*name;
	int		len;

	name = ft_env_name(arg);
	if (!name)
	{
		ft_printf("cant export, invalid name\n");
		return (NULL);
	}
	len = ft_strlen(name);
	if (name[len] == '=' && ft_strlen(name + len + 1))
	{
		ft_env_set(env, name, name + len + 1);
		return (env);
	}
	ret = ft_env_dup(env);
	len = ft_split_len(ret);
	if (!ft_strchr(arg, '='))
		ret[len] = ft_strjoin(arg, "=");
	else
		ret[len] = ft_strdup(arg);
	ret[len + 1] = NULL;
	ft_split_free(env);
	return (ret);
}

char	**ft_unset(char **env, char *name)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(name, env[i], len) && env[i][len] == '=')
		{
			free(env[i]);
			j = i;
			while (env[j + 1])
			{
				env[j] = env[j + 1];
				j++;
			}
			env[j] = NULL;
		}
		i++;
	}
	return (env);
}

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
