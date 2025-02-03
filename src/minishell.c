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

int	g_last_signal = 0;

char	*ft_get_prompt(char **env, char *exit_status)
{
	char	*ret;
	char	*pwd;
	//char	t1;
	//char	t2;

	//t1 = '>';
	//t2 = '$';
	pwd = ft_getcwd();
	if (ft_strchr(pwd, '/') == ft_strrchr(pwd, '/'))
		ret = ft_strjoin("minishell$ ", pwd);
	else if (!ft_strncmp(pwd, ft_env_get(env, "HOME"), ft_strlen(pwd) + 1))
		ret = ft_strdup("minishell$ ~");
	else
		ret = ft_strjoin("minishell$ ./", ft_strrchr(pwd, '/') + 1);
	free(pwd);
	if (!ft_strncmp(exit_status, "0", 2))
		pwd = ft_strjoin(ret, " > " CLR_GRN ":3" CLR_RST " $ ");
	else
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
	m->last_command = m->cash;
	m->triple = ft_split_triple(m->line);
	m->exit_res = get_redir_info(m);
	m->i = 0;
	m->pids[0] = 0;
}

void	letsgo_cleanup(t_mshl *m)
{
	if (m->fd_in != -1)
		close(m->fd_in);
	if (m->fd_out != -1)
		close(m->fd_out);
	m->i = 0;
	while (m->triple[m->i])
	{
		if (m->pids[m->i] > 0)
			waitpid(m->pids[m->i], &m->waitpid_status, 0);
		m->i++;
		m->exit_res = ((m->waitpid_status & 0xff00) >> 8);
	}

	ft_free_triple(m->triple);
	m->redir_in = ft_free(m->redir_in);
	m->redir_out = ft_free(m->redir_out);
	free(m->exit_status);
	m->exit_status = ft_itoa(m->exit_res);
}

int	ft_open_redirs(t_mshl *m)
{
	m->prevfd = STDIN_FILENO;
	m->fd_in = -1;
	m->fd_out = -1;
	if (m->redir_heredoc == 1)
	{
		m->tmp_heredoc = "/tmp/minishell_romain_heredoc_tmp.txt";
		m->fd_in = open(m->tmp_heredoc, O_CREAT | O_WRONLY | O_TRUNC, 0600);
		if (m->fd_in < 0)
			return (1 + (0 * ft_printf("open failed\n")));
		while (1)
		{
			ft_printf("heredoc minishell> ");
			m->line2 = get_next_line(STDIN_FILENO);
			if (!m->line2 || !ft_strncmp(m->line2, m->redir_in, 999))
				break ;
			write(m->fd_in, m->line2, ft_strlen(m->line2));
			write(m->fd_in, "\n", 1);
			free(m->line2);
		}
		m->line2 = ft_free(m->line2);
		close(m->fd_in);
		m->fd_in = open(m->tmp_heredoc, O_RDONLY);
		if (m->fd_in < 0)
			return (2 + (0 * ft_printf("open failed\n")));
	}
	else if (m->redir_in)
	{
		m->fd_in = open(m->redir_in, O_RDONLY);
		if (m->fd_in < 0)
			return (3 + (0 * ft_printf("redir in file doesnt exist\n")));
	}
	if (m->redir_out)
	{
		if (m->redir_app == 0)
			m->flags = O_CREAT | O_WRONLY | O_TRUNC;
		else
			m->flags = O_CREAT | O_WRONLY | O_APPEND;
		m->fd_out = open(m->redir_out, m->flags, 0644);
		if (m->fd_out < 0)
			return (4 + (0 * ft_printf("open failed\n")));
	}
	return (0);
}

void ft_cleanup_pipe(t_mshl *m)
{
	if (m->prevfd != STDIN_FILENO)
		close(m->prevfd);
	if (!m->is_last)
		close(m->pipefd[1]);
	if (m->is_last)
		m->prevfd = STDIN_FILENO;
	else
		m->prevfd = m->pipefd[0];
}

void ft_ready_pipe(t_mshl *m)
{
	m->comm = m->triple[m->i];
	ft_strtolower(m->comm[0]);
	m->is_first = (m->i == 0);
	m->is_last = (m->triple[m->i + 1] == NULL);
	if (!m->is_last && pipe(m->pipefd) < 0)
		exit(5 + (0 * ft_printf("pipe failed\n")));
	if (m->fd_in != -1 && m->is_first)
		m->prevfd = m->fd_in;
	if (m->fd_out != -1 && m->is_last)
		m->pipefd[1] = m->fd_out;
}

void	letsgo(t_mshl *m)
{
	letsgo_getready(m);
	ft_open_redirs(m);
	//
	//ft_printf("in:%s, heredoc:%d, out:%s, append:%d\n", m->redir_in, m->redir_heredoc, m->redir_out, m->redir_app);
	//ft_print_triple_comm(m->triple);
	//
	m->comm = m->triple[0];
	ft_strtolower(m->comm[0]);
	if (!m->triple[1] && is_builtin_dontfork(m->comm[0]))
		m->exit_res = ft_exec_builtin(m);
	while (!m->exit_res && m->triple[m->i] && !is_builtin_dontfork(m->triple[0][0]))
	{
		ft_ready_pipe(m);
		ft_exec_pipesegment(m);
		ft_cleanup_pipe(m);
		//
		//ft_printf("pipe loop %d, %s\n", m->i, m->comm[0]);
		//
		m->i++;
	}
	letsgo_cleanup(m);
}

void	init_t_mshl(t_mshl *m, char **envp_main)
{
	init_signals();
	ft_printf("(✿ ◕‿ ◕) hi~~ welcome to minishell (っ＾▿＾)っ\n");
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
	while (argc == 1 && argv[0])
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
			return (0 + (0 * ft_printf("o(*￣○￣)ゝ ctrl+d, bye minishell\n")));
		free(m.line);
	}
	return (2 + (0 * ft_printf("usage: %s\n", "./minishell")));
}
