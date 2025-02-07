/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:14:15 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/06 17:14:24 by rdomange         ###   ########.fr       */
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

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (NULL);
	i = 0;
	ret = ft_strdup(name);
	while (ft_isalnum(name[i]) || name[i] == '_')
		i++;
	ret[i] = 0;
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
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
		{
			free(name);
			return (&(env[i][len + 1]));
		}
		i++;
	}
	free(name);
	return (NULL);
}

int	ft_env_set(char **env, char *name, char *val)
{
	int		i;
	int		len;
	char	*str;

	name = ft_env_name(name);
	if (!name)
		return (-1);
	len = ft_strlen(name);
	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
		{
			free(env[i]);
			str = ft_strjoin(name, "=");
			env[i] = ft_strjoin(str, val);
			free(str);
			free(name);
			return (1);
		}
		i++;
	}
	free(name);
	return (0);
}
