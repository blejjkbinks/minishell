/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:34:28 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/20 13:34:29 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_redirection(char *str, int *rin, int *rout);
int	find_mode(char *str, int *i, int *mode);
int	trim_redirection(char *str, int mode, int *rin, int *rout);
int	open_redirection(char *str, int mode, int *rin, int *rout);
int	open_heredoc(char *str);

int	find_redirection(char *str, int *rin, int *rout)
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
			if (find_mode(str, &i, &mode))
				return (258);
			if (trim_redirection(str + i, mode, rin, rout))
				return (1);
			i = 0;
			q = 0;
		}
		else
			i++;
	}
	return (0);
}

int	find_mode(char *str, int *i, int *mode)
{
	*mode = str[*i];
	(*i)++;
	if ((!str[*i] || str[*i] == '<' || str[*i] == '>') && str[*i] != *mode)
		return (1);
	if (str[*i] == *mode)
	{
		(*mode)++;
		(*i)++;
		if (!str[*i] || str[*i] == '<' || str[*i] == '>')
			return (2);
	}
	return (0);
}

int	trim_redirection(char *str, int mode, int *rin, int *rout)
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
	ft_memmove(str, &str[len], ft_strlen(&str[len]) + 1);
	dup[j] = 0;
	ft_strtrim_quotes(dup);
	return (open_redirection(dup, mode, rin, rout));
}

int	open_redirection(char *str, int mode, int *rin, int *rout)
{
	if ((mode == '>' || mode == '>' + 1) && *rout)
		close(*rout);
	if ((mode == '<' || mode == '<' + 1) && *rin)
		close(*rin);
	if (mode == '>')
		*rout = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (mode == '>' + 1)
		*rout = open(str, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (mode == '<')
		*rin = open(str, O_RDONLY);
	if (mode == '<' + 1)
		*rin = open_heredoc(str);
	if (MS_DEBUG && ft_printf("MS_DEBUG: OPEN: "))
		ft_printf("'%s' m:%c, in:%d, out:%d\n", str, mode, *rin, *rout);
	if (*rin < 0 || *rout < 0)
	{
		if (*rin != -5)
			ft_printf("minishell: %s: no such file or directory\n", str);
		free(str);
		return (4);
	}
	free(str);
	return (0);
}

/*
int	open_heredoc(char *str)
{
	int		fd;
	char	*line;

	fd = open(MS_HEREDOC_PATH, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	while (1)
	{
		ft_printf("'%s'> ", str);
		line = get_next_line(0);
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
*/
