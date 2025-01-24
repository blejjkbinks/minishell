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

void	ft_print_triple_comm(char ***triple)
{
	int	i;
	int	j;
	int	k;

	ft_printf("vvvvv\n");
	i = 0;
	while (triple[i])
	{
		j = 0;
		while (triple[i][j])
		{
			k = 0;
			while (triple[i][j][k])
			{
				ft_printf("%c", triple[i][j][k]);
				k++;
			}
			if (triple[i][j + 1])
				ft_printf(",");
			else
				ft_printf(";");
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("^^^^\n");
}

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
		pwd = ft_strjoin(ret, " > " CLR_GRN ":3" CLR_RST " $ ");
	else
		//pwd = ft_strjoin(ret, " > :( $ ");
		pwd = ft_strjoin(ret, " > " CLR_RED ":(" CLR_RST " $ ");
	free(ret);
	return (pwd);
}

void	letsgo_getready(t_mshl *m)
{
	m->cash = m->line;
	m->line = cash_money(*m);
	if (ft_strnstr(m->cash, "!!", ft_strlen(m->cash)))
		ft_printf("!!:%s\n", m->line);
	free(m->last_command);
	m->last_command = m->cash;	//yikes		//???note to self: write real comments #yikes
	m->triple = ft_split_triple(m->line);
	m->exit_res = get_redir_info(m);
	ft_print_triple_comm(m->triple);
	ft_printf("in:%s, heredoc:%d, out:%s, append:%d\n", m->redir_in, m->redir_heredoc, m->redir_out, m->redir_app);
	m->redir_in = NULL;
	m->redir_out = NULL;
	m->i = 0;
}

void	letsgo_cleanup(t_mshl *m)
{
	ft_free_triple(m->triple);
	m->redir_in = ft_free(m->redir_in);
	m->redir_out = ft_free(m->redir_out);
	free(m->exit_status);
	m->exit_status = ft_itoa(m->exit_res);
}

void	letsgo(t_mshl *m)
{
	letsgo_getready(m);
	if (!m->exit_res && m->triple[m->i]) //was while but need to handle differently later
	{
		m->comm = m->triple[m->i];
		ft_strtolower(m->comm[0]);
		if (is_builtin(m->comm[0]) || ft_strchr(m->comm[0], '='))
			m->exit_res = exec_builtin(m);
		else
			m->exit_res = exec_fork(m->comm, m->env);
		m->i++;
	}
	letsgo_cleanup(m);
}

void	init_t_mshl(t_mshl *m, char **envp_main)
{
	m->redir_in = NULL;
	m->redir_out = NULL;
	m->env = ft_env_dup(envp_main);
	m->env = ft_export(m->env, "OLDPWD=");
	m->env_extra = ft_split("yea=YEAAA,extra=EXXXTRA", ",");
	m->line = ft_itoa(ft_atoi(ft_env_get(m->env, "SHLVL")) + 1);
	ft_env_set(m->env, "SHLVL", m->line);
	free(m->line);
	m->exit_status = ft_itoa(0);
	m->last_command = ft_strdup("^^\'");
}

int	main(int argc, char **argv, char **envp_main)
{
	t_mshl	m;

	if (argc == 1)
		init_t_mshl(&m, envp_main);
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
		if (!m.line)
			return (1 + (0 * ft_printf("readline gave NULL??\n")));
		free(m.line);
	}
	return (2 + (0 * ft_printf("usage: %s\n", argv[0])));
}
