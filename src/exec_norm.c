/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:50:05 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/04 16:50:14 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_magic(t_mshl *b, int x)
{
	if (x == 1 && ft_env_get(b->env, b->comm[0]))
		ft_env_set(b->env, b->comm[0], ft_strchr(b->comm[0], '=') + 1);
	else if (x == 1)
		b->env_extra = ft_export(b->env_extra, b->comm[0]);
	if (x == 0)
		b->env = ft_export(b->env, b->comm[1]);
	if (ft_export_magic_norm(b, x))
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

int	ft_exec_builtin(t_mshl *b)
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
	if (!ft_strncmp(b->comm[0], "env_extra", 10))
		return (ft_env(b->env_extra));
	if (!ft_strncmp(b->comm[0], "which", 10))
		return (ft_which_print(b->comm, b->env));
	if (!ft_strncmp(b->comm[0], "exit", 10))
		exit (0 + (0 * ft_printf("byebye minishell (˶ᵔ ᵕ ᵔ˶)ノ\n")));
	return (-1);
}
