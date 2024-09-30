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
		ret = ft_strjoin("minishell$ ", pwd);
	else if (!ft_strncmp(pwd, ft_env_get(env, "HOME"), ft_strlen(pwd) + 1))
		ret = ft_strdup("minishell$ ~");
	else
		ret = ft_strjoin("minishell$ ./", ft_strrchr(pwd, '/') + 1);
	free(pwd);
	if (!ft_strncmp(exit_status, "0", 2))
		//pwd = ft_strjoin(ret, " > :3 $ ");
		pwd = ft_strjoin(ret, " > " CLR_GRN ":3" CLR_RESET " $ ");
	else
		//pwd = ft_strjoin(ret, " > :( $ ");
		pwd = ft_strjoin(ret, " > " CLR_RED ":(" CLR_RESET " $ ");
	free(ret);
	return (pwd);
}

void	letsgo(t_mshl *m)
{
	m->i = 0;
	m->cash = m->line;
	m->line = cash_money(*m);
	//ft_printf("cash:%s\n", m->line);
	if (ft_strnstr(m->cash, "!!", ft_strlen(m->cash)))
		ft_printf("!!:%s\n", m->line);
	free(m->last_command);
	m->last_command = m->cash;		//yikes
	m->pipe = ft_split_pipes(m->line);
	/*
	ft_printf("SPLIT m->pipe:");
	for (int p = 0; m->pipe[p]; p++)
		ft_printf("%s,", m->pipe[p]);
	ft_printf("\n");
	*/
	while (m->pipe[m->i])
	{
		m->comm = ft_split_quotes(m->pipe[m->i]);
		/*
		ft_printf("SPLIT m->comm:");
		for (int p = 0; m->comm[p]; p++)
			ft_printf("%s,", m->comm[p]);
		ft_printf("\n");
		*/
		if (is_builtin(m->comm[0]) || ft_strchr(m->comm[0], '='))
			m->exit_res = exec_builtin(m);
		else
			m->exit_res = exec_fork(m->comm, m->env);
		ft_split_free(m->comm);
		m->i++;
	}
	ft_split_free(m->pipe);
	if (ft_atoi(m->exit_status) != m->exit_res)
	{
		free(m->exit_status);
		m->exit_status = ft_itoa(m->exit_res);
	}
}

int	main(int argc, char **argv, char **envp_main)
{
	t_mshl	m;

	if (argc == 1)
	{
		m.env = ft_env_dup(envp_main);
		m.env = ft_export(m.env, "OLDPWD=");
		m.env_extra = ft_split("yea=YEA,extra=EXTRA", ",");
		m.line = ft_itoa(ft_atoi(ft_env_get(m.env, "SHLVL")) + 1);
		ft_env_set(m.env, "SHLVL", m.line);
		free(m.line);
		m.exit_status = ft_itoa(0);
		m.last_command = ft_strdup("^^");
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
			//free(m.last_command);
			//m.last_command = ft_strdup(m.line);

		}
		if (!m.line)
			return (1 + (0 * ft_printf("readline gave NULL??\n")));
		free(m.line);
	}
	return (2 + (0 * ft_printf("usage: %s\n", argv[0])));
}
