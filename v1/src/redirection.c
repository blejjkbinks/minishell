/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:33:54 by rdomange          #+#    #+#             */
/*   Updated: 2024/10/02 17:33:55 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	index_redirection(char *line, t_mshl *r)
{
	while (line[r->i])
	{
		quoted(line[r->i], &r->quote);
		if (!r->quote && line[r->i] == ' ' && line[r->i + 1] == '<')
		{
			if (r->redir_in_index != -1)
				return (2);
			r->redir_in_index = r->j;
		}
		if (!r->quote && line[r->i] == ' ' && line[r->i + 1] == '>')
		{
			if (r->redir_out_index != -1)
				return (3);
			r->redir_out_index = r->j;
		}
		r->c = line[r->i];
		r->d = line[r->i + 1];
		if (!r->quote && (r->c != ' ' && (r->d == ' ' || r->d == 0)))
			r->j++;
		if (!r->quote && r->c == '|' && r->d != '|')
			r->j--;
		r->i++;
	}
	return (0);
}

int	trim_redirection_in(t_mshl *r)
{
	r->i = 0;
	if (r->redir_in_index < 0)
		return (0);
	while (r->triple && r->triple[r->i])
	{
		r->j = 0;
		while (r->triple[r->i][r->j])
		{
			if (r->redir_in_index == 0)
				return (trim_in_norm(r));
			r->redir_in_index--;
			r->j++;
		}
		r->i++;
	}
	return (5);
}

int	trim_redirection_out(t_mshl *r)
{
	r->i = 0;
	if (r->redir_out_index < 0)
		return (0);
	while (r->triple && r->triple[r->i])
	{
		r->j = 0;
		while (r->triple[r->i][r->j])
		{
			if (r->redir_out_index == 0)
				return (trim_out_norm(r));
			r->redir_out_index--;
			r->j++;
		}
		r->i++;
	}
	return (8);
}

int	get_redir_info(t_mshl *m)
{
	int	redir_token;

	m->i = 0;
	m->j = 0;
	m->quote = 0;
	m->redir_in_index = -1;
	m->redir_out_index = -1;
	m->redir_app = -1;
	m->redir_heredoc = -1;
	redir_token = index_redirection(m->line, m);
	if (!redir_token)
		redir_token = trim_redirection_in(m);
	if (!redir_token)
		redir_token = trim_redirection_out(m);
	if (redir_token)
		return (258 + (0 * ft_printf("minishell: invalid token ><\n")));
	return (0);
}
