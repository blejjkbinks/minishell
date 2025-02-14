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

	len = ft_env_name(arg, NULL);
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

char	**ft_unset(char **env, char *name_src)
{
	char	*name;
	int		i;
	int		j;
	int		len;

	len = ft_env_name(name_src, &name);
	if (!name)
		return (NULL);
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
	if (x == 0)
		env[0] = ft_export(env[0], arg);
	if (x == 0 && (ft_env_get(env[1], arg) && !ft_strchr(arg, '=')))
		ft_env_set(env[0], arg, ft_env_get(env[1], arg));
	if (x == 1 && ft_env_get(env[0], arg))
		env[0] = ft_export(env[0], arg);
	else if (x == 1)
		env[1] = ft_export(env[1], arg);
	if (x == 2 || x == 4)
		ft_unset(env[(2 * (x == 4))], arg);
	if (x == 2 || x == 0)
		ft_unset(env[1], arg);
	if (x == 3 && !ft_strchr(arg, '=') && ft_env_get(env[2], arg))
		ft_printf("alias: %s=%s\n", arg, ft_env_get(env[2], arg));
	if (x == 3 && !ft_strchr(arg, '=') && !ft_env_get(env[2], arg) && arg)
		ft_printf("minishell: alias: %s: not found\n", arg);
	if (x == 3 && arg[ft_env_name(arg, NULL)] == '=')
		env[2] = ft_export(env[2], arg);
	if (x == 3 && !arg)
		ft_env(env[2]);
	if (arg[ft_env_name(arg, NULL)] != '=' && arg[ft_env_name(arg, NULL)] != 0)
		return (1);
	return (!ft_env_name(arg, NULL));
}
