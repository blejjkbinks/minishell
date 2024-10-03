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

	ret = (char **)ft_malloc((ft_split_len(env) + 1 + 1) * sizeof(char *));
	i = 0;
	while (env && env[i])
	{
		ret[i] = ft_strdup(env[i]);
		i++;
	}
	ret[i] = NULL;
	ret[i + 1] = NULL;
	return (ret);
}

char	*ft_env_name(char *name)
{
	char	*ret;
	int		i;

	//ft_printf("in ft_env_name, asked: %s\n", name);
	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (NULL);
	i = 0;
	ret = ft_strdup(name);
	while (ft_isalnum(name[i]) || name[i] == '_')
		i++;
	ret[i] = 0;
	//ft_printf("in ft_env_name, returning: %s\n", ret);
	return (ret);
}

int	ft_env_namelen(char *name)
{
	int	len;

	name = ft_env_name(name);
	len = ft_strlen(name);
	if (name)
		free(name);
	return (len);
}

char	*ft_env_get(char **env, char *name)
{
	int	i;
	int	len;

	name = ft_env_name(name);
	if (!name)
	{
		//ft_printf("in ft_env_get, invalid name\n");
		return (NULL);
	}
	len = ft_strlen(name);
	//ft_printf("in ft_env_get, asked for: %s\n", name);
	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
		{
			free(name);
			//ft_printf("in ft_env_get, returning: %s\n", &(env[i][len + 1]));
			return (&(env[i][len + 1]));
		}
		i++;
	}
	free(name);
	//ft_printf("in ft_env_get, didnt find\n");
	return (NULL);
}

int	ft_env_set(char **env, char *name, char *val)
{
	int		i;
	int		len;
	char	*str;

	name = ft_env_name(name);
	if (!name)
	{
		//ft_printf("in ft_env_set, inavlid name\n");
		return (-1);
	}
	len = ft_strlen(name);
	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
		{
			free(env[i]);
			str = ft_strjoin(name, "=");
			env[i] = ft_strjoin(str, val);
			//ft_printf("in ft_env_set, now: %s\n", env[i]);
			free(str);
			free(name);
			return (1);
		}
		i++;
	}
	free(name);
	//ft_printf("in ft_env_set, didnt find\n");
	return (0);
}

char	**ft_export(char **env, char *arg)
{
	char	**ret;
	int		len;

	len = ft_env_namelen(arg);
	if (!len || (arg[len] != 0 && arg[len] != '='))
	{
		ft_printf("minishell: export: \'%s\': not a valid identifier\n", arg);
		return (env);
	}
	if (ft_env_get(env, arg))
	{
		//ft_printf("in ft_export, %s already in env\n", arg);
		if (arg[len] == '=')
			ft_env_set(env, arg, &arg[len + 1]);
		return (env);
	}
	ret = env;
	env = ft_env_dup(env);
	ft_split_free(ret);
	//ft_printf("in ft_export, duping at %d\n", ft_split_len(env));
	if (arg[len] == '=')
		env[ft_split_len(env)] = ft_strdup(arg);
	else
		env[ft_split_len(env)] = ft_strjoin(arg, "=");
	return (env);
}

char	**ft_unset(char **env, char *name)
{
	int	i;
	int	j;
	int	len;

	//ft_printf("in ft_unset: %s\n", name);
	name = ft_env_name(name);
	if (!name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env && env[i])
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
	free(name);
	return (env);
}

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
