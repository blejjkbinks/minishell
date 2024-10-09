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
	r->k = 0;
	r->j = 0;
	r->quote = 0;
	r->redir_in_index = -1;
	r->redir_out_index = -1;
	while (line[r->k])
	{
		quoted(line[r->k], &r->quote);
		if (!r->quote && line[r->k] == '<')
		{
			if (r->redir_in_index != -1)
				return (1);
			r->redir_in_index = r->j;
		}
		if (!r->quote && line[r->k] == '>')
		{
			if (r->redir_out_index != -1)
				return (1);
			r->redir_out_index = r->j;
		}
		if (!r->quote && line[r->k] != ' ' && ((line[r->k + 1] == ' ') || line[r->k + 1] == 0))
			r->j++;
		r->k++;
	}
	ft_printf("index in:%d, out:%d\n", r->redir_in_index, r->redir_out_index);
	return (0);
}

int	trim_redirection(t_mshl *r)
{
	r->fdr_in = -1;
	r->fdr_out = -1;
	r->redir_out = NULL;
	//return (0);
	if (r->redir_out_index >= 0)
	{
		if (!r->comm[r->redir_out_index + 1])
			return (1);
		if (r->comm[r->redir_out_index][1] == 0)
			//r->fdr_out = open(r->comm[r->redir_out_index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			r->redir_app = 0;
		else if (r->comm[r->redir_out_index][1] == '>' && r->comm[r->redir_out_index][2] == 0)
			//r->fdr_out = open(r->comm[r->redir_out_index + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			r->redir_app = 1;
		else
			return (1);
		r->redir_out = ft_strdup(r->comm[r->redir_out_index + 1]);
		ft_split_remove(r->comm, r->redir_out_index);
		ft_split_remove(r->comm, r->redir_out_index);
	}
	if (r->redir_in_index >= 0)
	{
		if (!r->comm[r->redir_out_index + 1])
			return (1);
	}
	ft_printf("fdr in:%d, out:%d\n", r->fdr_in, r->fdr_out);
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