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

static int	find_redirection(char *str, int *rin, int *rout);
static int	trim_redirection(char *str, int mode, int *rin, int *rout);
static int	open_redirection(char *str, int mode, int *rin, int *rout);
static int	open_heredoc(char *str);

int	redirection(char **pipe, int *pidfd)
{
	int	i;

	i = 0;
	while (pipe && pipe[i])
	{
		if (find_redirection(pipe[i], &pidfd[(3 * i) + 1], &pidfd[(3 * i) + 2]))
			return (ft_printf("minishell: invalid token ><\n"));
		i++;
	}
	return (0);
}

static int	find_redirection(char *str, int *rin, int *rout)
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
				return (1);
			if (str[i] == mode)
			{
				mode++;
				i++;
				if (!str[i] || str[i] == '<' || str[i] == '>')
					return (2);
			}
			if (trim_redirection(str + i, mode, rin, rout))
				return (3);
			i = 0;
			q = 0;
		}
		else
			i++;
	}
	return (0);
}

static int	trim_redirection(char *str, int mode, int *rin, int *rout)
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
	while (dup[j] && (!ft_strchr("> <", dup[j]) || q))
	{
		ft_isquoted(dup[j], &q);
		j++;
	}
	len = j + k + 1 + (mode != '>' && mode != '<');
	str -= (1 + (mode != '>' && mode != '<'));
	//
	//ft_printf("from '%s' moving %d back\n", str, len);
	//
	ft_memmove(str, &str[len], ft_strlen(&str[len]) + 1);
	//
	//ft_printf("after moving:'%s'\n", str);
	//
	dup[j] = 0;
	ft_strtrim_quotes(dup);
	return (open_redirection(dup, mode, rin, rout));
	//
	//ft_printf("redir: mode:'%c', file:'%s'\n", mode, dup);
	//
}

static int	open_redirection(char *str, int mode, int *rin, int *rout)
{
	if (mode == '>')
		*rout = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (mode == '>' + 1)
		*rout = open(str, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (mode == '<')
		*rin = open(str, O_RDONLY);
	if (mode == '<' + 1)
		*rin = open_heredoc(str);
	if (MS_DEBUG)
		ft_printf("OPEN '%s' in %c mode, in:%d, out:%d\n", str, mode, *rin, *rout);
	free(str);
	if (*rin < 0 || *rout < 0)
		return (1 + (0 * ft_printf("failed to open %s\n", str)));
	return (0);
}

static int	open_heredoc(char *str)
{
	int		fd;
	char	*line;

	fd = open(MS_HEREDOC_PATH, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	while (1)
	{
		ft_printf("heredoc minishell> ");
		line = get_next_line(fd);
		if (!line || !ft_strcmp(line, str))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	ft_free(line);
	close(fd);
	fd = open(MS_HEREDOC_PATH, O_RDONLY);
	return (fd);
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