/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:58:56 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/07 16:59:02 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getcwd(void)
{
	int		cap;
	char	*str;
	char	*buff;

	cap = DEFAULT_CAP;
	while (1)
	{
		buff = (char *)ft_malloc((cap + 1) * sizeof(char));
		if (!buff)
			return (NULL);
		str = getcwd(buff, cap);
		if (str)
			return (str);
		free(buff);
		if (errno != ERANGE)
			return (NULL);
		cap *= 2;
	}
}

int	ft_pwd(void)
{
	char	*str;

	str = ft_getcwd();
	ft_printf("%s\n", str);
	free(str);
	return (0);
}

int	ft_cd_oldpwd(char **arg, char **env, int err)
{
	char	*str;

	if (err == ENOENT)
		ft_printf("cd: no such file or directory: %s\n", arg[1]);
	if (err == ENOTDIR)
		ft_printf("cd: not a directory: %s\n", arg[1]);
	if (!err)
		ft_env_set(env, "OLDPWD", ft_env_get(env, "PWD"));
	str = ft_getcwd();
	ft_env_set(env, "PWD", str);
	free(str);
	if (err == ENOENT)
		return (1);
	return (0);
}

int	ft_cd(char **arg, char **env)
{
	errno = 0;
	if (ft_split_len(arg) == 1)
		chdir(ft_env_get(env, "HOME"));
	else if (ft_split_len(arg) == 2)
	{
		if (arg[1][0] == '-' && ft_strlen(arg[1]) == 1)
		{
			if (!ft_strlen(ft_env_get(env, "OLDPWD")))
				return (1 + 0 * ft_printf("minishell: cd: OLDPWD not set\n"));
			else
			{
				ft_printf("%s\n", ft_env_get(env, "OLDPWD"));
				chdir(ft_env_get(env, "OLDPWD"));
			}
		}
		else
			chdir(arg[1]);
	}
	return (ft_cd_oldpwd(arg, env, errno));
}