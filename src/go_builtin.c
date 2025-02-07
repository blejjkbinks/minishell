/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:15:14 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/06 17:15:15 by rdomange         ###   ########.fr       */
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

static	int	ft_exit_builtin(t_mshl *m)
{
	int		i;
	char	*a;
	char	*b;
	char	*c;

	a = "minishell: exit: ";
	b = "too many arguments";
	c = "numeric argument required";
	if (m->comm[1] && m->comm[2])
		return (1 + (0 * ft_printf("%s%s\n", a, b)));
	if (m->comm[1])
	{
		i = 0;
		while (m->comm[1][i])
		{
			if (!ft_isdigit(m->comm[1][i]))
				return (1 + (0 * ft_printf("%s%s: %s\n", a, m->comm[1], c)));
			i++;
		}
		ft_printf("o(*￣○￣)ゝ kill%s bye minishell\n", m->comm[1]);
		exit(ft_atoi(m->comm[1]));
	}
	exit (0 + (0 * ft_printf("byebye minishell (˶ᵔ ᵕ ᵔ˶)ノ\n")));
}

int	ft_exec_builtin(char **comm, char **env[3])
{
	if (!ft_strcmp(b->comm[0], "echo"))
		return (ft_echo(b->comm));
	if (!ft_strcmp(b->comm[0], "cd"))
		return (ft_cd(b->comm, b->env));
	if (!ft_strcmp(b->comm[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(b->comm[0], "export"))
		return (ft_export_magic(b, 0));
	if (ft_strchr(b->comm[0], '='))
		return (ft_export_magic(b, 1));
	if (!ft_strcmp(b->comm[0], "unset"))
		return (ft_export_magic(b, 2));
	if (!ft_strcmp(b->comm[0], "env"))
		return (ft_env(b->env));
	if (!ft_strcmp(b->comm[0], "env_extra"))
		return (ft_env(b->env_extra));
	if (!ft_strcmp(comm[0], "alias"))
		return ();
	if (!ft_strcmp(comm[0], "unalias"))
		return ();
	if (!ft_strcmp(b->comm[0], "which"))
		return (ft_which_print(b->comm, b->env));
	if (!ft_strcmp(b->comm[0], "exit"))
		return (ft_exit_builtin(b));
	return (-1);
}
