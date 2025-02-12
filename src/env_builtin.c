/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:32:32 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/06 16:38:16 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (arg[len] == '=')
			ft_env_set(env, arg, &arg[len + 1]);
		return (env);
	}
	ret = ft_env_dup(env);
	ft_split_free(env);
	if (arg[len] == '=')
		ret[ft_split_len(ret)] = ft_strdup(arg);
	else 
		ret[ft_split_len(ret)] = ft_strjoin(arg, "=");
	return (ret);
}

char	**ft_unset(char **env, char *name)
{
	int	i;
	int	j;
	int	len;

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
			while (env[j++ + 1])
				env[j - 1] = env[j];
			env[j - 1] = NULL;
		}
		i++;
	}
	free(name);
	return (env);
}

int	ft_export_magic(char *arg, char ***env, int x)
{
	if (x == 0 && (ft_env_get(env[1], arg) || ft_strchr(arg, '=')))
		env[0] = ft_export(env[0], arg);
	if (x == 0 && (ft_env_get(env[1], arg) && !ft_strchr(arg, '=')))
		ft_env_set(env[0], arg, ft_env_get(env[1], arg));
	if (x == 0)
		ft_unset(env[1], arg);
	//
	if (x == 1 && ft_env_get(env[0], arg))
		env[0] = ft_export(env[0], arg);
	else if (x == 1)
		env[1] = ft_export(env[1], arg);
	//
	if (x == 2)
		ft_unset(env[0], arg);
	if (x == 2)
		ft_unset(env[1], arg);
	//exporting/showing alias, needs work lmao
	if (x == 3 && !ft_strchr(arg, '=') && ft_strlen(ft_env_get(env[3], arg)))
		ft_printf("alias: %s\n", ft_env_get(env[3], arg));
	if (x == 3 && !ft_strchr(arg, '=') && !ft_strlen(ft_env_get(env[3], arg)) && arg)
		ft_printf("minishell: alias: %s: not found\n");
	if (x == 3 && ft_env_namelen(arg) && ft_strchr(arg, '='))
		env[2] = ft_export(env[2], arg);
	if (x == 3 && !arg)
		ft_env(env[2]);
	//
	if (x == 4)
		ft_unset(env[2], arg);
	if (!ft_env_namelen(arg))
		return (1);
//	if (x != 1 && arg + 1)		//need to pass "**comm" not "*comm", recursion with "arg + 1"
//		return (ft_export_magic(arg + 1, env, x));
	return (0);
}
