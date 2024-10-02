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

//after separating pipes
//before splitting arguments
//line is the raw command with quotes;

int	index_redirection(char *line, t_mshl *r)
{
	r->i = 0;
	r->j = 0;
	r->quote = 0;
	r->redir_in_index = 0;
	r->redir_out_index = 0;
	while (line[r->i])
	{
		quoted(line[r->i], &r->quote);
		if (!r->quote && line[r->i] != ' ' && ((line[r->i + 1] == ' ') || line[r->i + 1] == 0))
			r->j++;
		if (!r->quote && line[r->i] == '<')
		{
			if (r->redir_in_index)
				return (1);
			r->redir_in_index = r->j;
		}
		if (!r->quote && line[r->i] == '>')
		{
			if (r->redir_out_index)
				return (1);
			r->redir_out_index = r->j;
		}
		r->i++;
	}
	return (0);
}

int	trim_redirection(t_mshl *r)
{
	if (r->redir_out_index)
	{
		if (!r->comm[r->redir_out_index + 1])
			return (1);
		if (r->comm[r->redir_out_index][1] == 0)
			r->fdr_out = open(r->comm[r->redir_out_index + 1], O_WRONLY | O_CREATE | O_TRUNC, 0644);
			//r->redir_app = 0;
		else if (r->comm[r->redir_out_index][1] == '>' && r->comm[r->redir_out_index][2] == 0)
			r->fdr_out = open(r->comm[r->redir_out_index + 1], O_WRONLY | O_CREATE | O_APPEND, 0644);
			//r->redir_app = 1;
		else
			return (1);
		if (r->fdr_out < 0)
			return (1);
		ft_split_remove(r->comm, r->redir_in_index);
		ft_split_remove(r->comm, r->redir_in_index + 1);
	}
	if (r->redir_in_index)
	{
		if (!r->comm[r->redir_out_index + 1])
			return (1);
	}
	return (0);
}

/*int	split_redirection(t_mshl *r)
{
	int	i;

	r->redir_in = NULL;
	r->redit_out = NULL;
	i = 0;
	while (r->comm[i])
	{
		if (r->comm[i][0] == '>')
		{
			if (r->comm[i][1] == 0)
				r->redir_app = 0;
			else if (r->comm[i][1] == '>' && r->comm[i][2] == 0)
				r->redir_app = 1;
			else
				return (1);
			if (!r->comm[i + 1] || r->redit_out)
				return (1);
			r->redir_out = r->comm[i + 1];
			//ft_split_remove(split, i);
			//ft_split_remove(split, i + 1);
		}
		if (r->comm[i][0] == '<')
		{
			if (!r->comm[i + 1] || r->redir_in || r->comm[i][1] != 0)
				return (1);
			r->redir_in = r->comm[i + 1];
		}
		i++;
	}
	if (!ft_strncmp(r->redir_in, r->redir_out, ft_strlen(r->redir_in)))
		return (1);
	return (0);
}*/