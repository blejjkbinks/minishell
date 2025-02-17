/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:31:15 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/11 13:31:16 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_redirection(char *str, int mode, int fdr[2]);

void	find_redirection(char *str, int fdr[2])
{
	int		mode;
	int		i;
	int		q;

	i = 0;
	q = 0;
	while (str && str[i])
	{
		ft_isquoted(str[i], &q);
		if (!q && (str[i] == '<' || str[i] == '>'))
		{
			mode = str[i];
			i++;
			if ((!str[i] || str[i] == '<' || str[i] == '>') && str[i] != mode)
				ft_printf("invalid token ><\n");
			if (str[i] == mode)
			{
				mode++;
				i++;
				if (!str[i] || str[i] == '<' || str[i] == '>')
					ft_printf("invalid token ><\n");
			}
			open_redirection(str + i, mode, fdr);
			i -= 2;
		}
		i++;
	}
}

static void	open_redirection(char *str, int mode, int fdr[2])
{
	char	*dup;
	int		j;
	int		k;
	int		q;
	int		len;

	q = 0;
	j = 0;
	k = 0;
	while (str[k] == ' ')
		k++;
	dup = ft_strdup(&str[k]);
	j = 0;
	while (dup[j] && (!ft_strchr("> <", dup[j]) || !q))
	{
		ft_isquoted(dup[j], &q);
		j++;
	}
	len = j + k + 1 + (mode != '>' && mode != '<');
	str -= (1 + (mode != '>' && mode != '<'));
	//
	//ft_printf("from '%s' moving %d back\n", str, len);
	//
	ft_memmove(str, &str[len], len + 1);
	//
	//ft_printf("after moving:'%s'\n", str);
	//
	dup[j] = 0;
	ft_strtrim_quotes(dup);
	ft_printf("redir: mode:'%c', file:'%s'\n", mode, dup);
	free(dup);
	fdr[0] = 0;
}

	/*
		if (!q && str[i] == '<')
		{
			mode = 'R';
			i++;
			if (str[i] == 0 || str[i] == '>')
				ft_printf("invalid token ><\n");
			if (str[i] == '<')
			{
				mode = 'H';
				i++;
				if (str[i] == 0 || str[i] == '>' || str[i] == '<')
					ft_printf("invalid token ><\n");
			}
			ft_printf("redir: mode:'%c', file:'%s'\n", mode, &str[i]);
		}
		if (!q && str[i] == '>')
		{
			mode = 'T';
			i++;
			if (str[i] == 0 || str[i] == '<')
				ft_printf("invalid token ><\n");
			if (str[i] == '>')
			{
				mode = 'A';
				i++;
				if (str[i] == 0 || str[i] == '>' || str[i] == '<')
					ft_printf("invalid token ><\n");
			}
			ft_printf("redir: mode:'%c', file:'%s'\n", mode, &str[i]);
		}*/