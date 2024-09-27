/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:59:41 by rdomange          #+#    #+#             */
/*   Updated: 2024/09/19 20:00:25 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_prompt(char **env, char *exit_status)
{
	char	*ret;
	char	*pwd;

	pwd = ft_getcwd();
	if (ft_strchr(pwd, '/') == ft_strrchr(pwd, '/'))
		ret = ft_strjoin("minishell> ", pwd);
	else if (!ft_strncmp(pwd, ft_env_get(env, "HOME"), ft_strlen(pwd) + 1))
		ret = ft_strdup("minishell> ~");
	else
		ret = ft_strjoin("minishell> ", ft_strrchr(pwd, '/') + 1);
	free(pwd);
	if (!ft_strncmp(exit_status, "0", 2))
		pwd = ft_strjoin(ret, " $ :3 $ ");
	else
		pwd = ft_strjoin(ret, " $ :( $ ");
	free(ret);
	return (pwd);
}

int	exec_builtin(t_mshl m)
{
	if (!ft_strncmp(m.line, "exit", 5))
		exit (0 + (0 * ft_printf("byebye\n")));
	if (!ft_strncmp(m.line, "env", 4))
		ft_env(m.env);
	return (0);
}

/*void	letsgo_pls(t_mshl *m)
{
	char	**pipe;
	char	**comm;
	int		i;

	m->i = 0;
	m->line = cash_money(*m);
	m->pipe = ft_split_pipes(m->line);
	while (pipe[i])
	{
		m->comm = ft_split_quotes(m->pipe[i]);
		m->j = ft_exec_builtin(m->comm);
		if (m->j == -1)
			m->j = ft_exec_fork(m->comm);
		ft_split_free(m->comm);
		m->i++;
	}
	ft_split_free(m->pipe);
	free(m->line)
	free(m->exit_status);
	m->exit_status = ft_atoi(ret);
}*/

void	letsgo(t_mshl *m)
{
	m->line = cash_money(*m);
	exec_builtin(*m);
	if (ft_strlen(m->line))
		ft_printf("%s\n", m->line);
}

int	main(int argc, char **argv, char **envp_main)
{
	t_mshl	m;

	if (argc == 1)
	{
		m.env = ft_env_dup(envp_main);
		m.env = ft_export(m.env, "OLDPWD");
		m.env = ft_export(m.env, "asd=123");
		m.line = ft_itoa(ft_atoi(ft_env_get(m.env, "SHLVL")) + 1);
		ft_env_set(m.env, "SHLVL", m.line);
		free(m.line);
		m.exit_status = ft_strdup("0");
	}
	while (argc == 1)
	{
		m.prompt = ft_get_prompt(m.env, m.exit_status);
		m.line = readline(m.prompt);
		free(m.prompt);
		if (ft_strlen(m.line))
		{
			add_history(m.line);
			letsgo(&m);
		}
		if (m.line)
			free(m.line);
	}
	return (0 * ft_printf("usage: %s\n", argv[0]));
}
