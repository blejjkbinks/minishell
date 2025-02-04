/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:10:57 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/04 17:11:07 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_redirs_in_norm(t_mshl *m)
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
	return (0);
}

int	ft_open_redirs_in(t_mshl *m)
{
	if (m->redir_heredoc == 1)
		return (ft_open_redirs_in_norm(m));
	else if (m->redir_in)
	{
		m->fd_in = open(m->redir_in, O_RDONLY);
		if (m->fd_in < 0)
			return (3 + (0 * ft_printf("redir in file doesnt exist\n")));
	}
	return (0);
}

int	ft_open_redirs(t_mshl *m)
{
	m->prevfd = STDIN_FILENO;
	m->fd_in = -1;
	m->fd_out = -1;
	if (ft_open_redirs_in(m))
		return (1);
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
