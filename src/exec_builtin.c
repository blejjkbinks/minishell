/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:15:14 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/12 15:21:27 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_which_print(char **arg, char **env);
static int	ft_exit_builtin(char **arg, char ***env);
static int	ft_echo(char **arg);
int			ft_source(char *arg, char ***env);

int	ft_exec_builtin(char **comm, char ***env)
{
	if (!ft_strcmp(comm[0], "echo"))
		return (ft_echo(comm));
	if (!ft_strcmp(comm[0], "cd"))
		return (ft_cd(comm, env[0]));
	if (!ft_strcmp(comm[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(comm[0], "env") || !ft_strcmp(comm[0], "env_extra"))
		return (ft_env(env[(!ft_strcmp(comm[0], "env_extra"))]));
	if (!ft_strcmp(comm[0], "export") && comm[1])
		return (ft_export_loop(comm, 1, 0, env));
	if (ft_isbuiltin(comm[0]) == 3)
		return (ft_export_loop(comm, 0, 1, env));
	if (!ft_strcmp(comm[0], "unset") && comm[1])
		return (ft_export_loop(comm, 1, 2, env));
	if (!ft_strcmp(comm[0], "alias"))
		return (ft_export_loop(comm, 1, 3, env));
	if (!ft_strcmp(comm[0], "unalias"))
		return (ft_export_loop(comm, 1, 4, env));
	if (!ft_strcmp(comm[0], "which"))
		return (ft_which_print(comm, env[0]));
	if (!ft_strcmp(comm[0], "source"))
		return (ft_source(comm[1], env));
	if (!ft_strcmp(comm[0], "exit"))
		return (ft_exit_builtin(comm, env));
	return (0);
}

static int	ft_which_print(char **arg, char **env)
{
	char	*str;
	int		i;
	int		ret;

	ret = 0;
	i = 1;
	while (arg[i])
	{
		if (ft_isbuiltin(arg[i]))
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

static	int	ft_exit_builtin(char **arg, char ***env)
{
	int		i;
	char	*s[3];

	s[0] = "minishell: exit: ";
	s[1] = "too many arguments";
	s[2] = ": numeric argument required";
	if (arg[1] && arg[2])
		return (1 + (0 * ft_printf("%s%s\n", s[0], s[1])));
	i = 0;
	while (arg[1] && arg[1][i++])
		if (!ft_isdigit(arg[1][i - 1]) && !(i == 1 && arg[1][0] == '-'))
			return (1 + (0 * ft_printf("%s%s%s\n", s[0], arg[1], s[2])));
	i = ((ft_atoi(arg[1]) % 256) + 256) % 256;
	if (!MS_CUTE)
		ft_printf("exit\n");
	if (MS_CUTE && !i)
		ft_printf("byebye minishell (˶ᵔ ᵕ ᵔ˶)ノ\n");
	if (MS_CUTE && i)
		ft_printf("o(*￣○￣)ゝ kill %d bye minishell\n", i);
	ft_split_free(env[0]);
	ft_split_free(env[1]);
	ft_split_free(env[2]);
	exit (i);
}

static int	ft_echo(char **arg)
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

int	ft_source(char *arg, char ***env)
{
	int		fd;
	char	*line;
	char	**comm;

	if (!arg)
		return (2 + (0 * ft_printf("source: give filename please\n")));
	fd = open(arg, O_RDONLY);
	if (fd < 0 && ft_strcmp(arg, "minishellrc"))
		return (1 + (0 * ft_printf("minishell: %s: no such file\n", arg)));
	line = get_next_line(fd);
	while (line)
	{
		comm = ft_split_quotes(line, ' ');
		ft_splittrim_quotes(comm);
		if (comm && !ft_strcmp(comm[0], "alias"))
			ft_export_magic(comm[1], env, 3, ft_env_name(comm[1], NULL));
		if (comm && !ft_strcmp(comm[0], "export"))
			ft_export_magic(comm[1], env, 0, ft_env_name(comm[1], NULL));
		ft_split_free(comm);
		ft_free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
