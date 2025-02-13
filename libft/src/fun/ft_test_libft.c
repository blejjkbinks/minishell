/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_libft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:43:15 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/05 19:49:59 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_test_split(char *line, char **pipe, char **comm, char *s);
static void	ft_test_showsplit(char **split, char *d, char n, int i);

void	ft_test_libft(void)
{
	char	*line;

	line = get_next_line(0 + (0 * ft_printf("testing libft :)\n$main> ")));
	while (ft_strcmp(line, "done"))
	{
		ft_printf("get_next_line got:'%s'", line);
		if (!ft_strcmp(line, "split"))
			ft_test_split(NULL, NULL, NULL, "split");
		if (!ft_strcmp(line, "r"))
			ft_printf("\n->%d", ft_mod_range(ft_random(), 100));
		line = get_next_line((ft_printf("\n$main> ")) * (long)ft_free(line));
	}
	ft_printf("done testing libft :)", ft_free(line));
}

static void	ft_test_split(char *line, char **pipe, char **comm, char *s)
{
	int	i;

	line = get_next_line(0 * ft_printf("\ntesting %s :)\n$%s> ", s, s));
	while (ft_strcmp(line, "done"))
	{
		ft_printf("splitting '%s'\n", line);
		ft_printf("unclosed quote?->%d.\n", ft_isquoted_closed(line));
		pipe = ft_split_quotes(line, '|');
		ft_test_showsplit(pipe, "[]", -1, 0);
		i = 0;
		while (pipe && pipe[i])
		{
			comm = ft_split_quotes(pipe[i], ' ');
			ft_test_showsplit(comm, "{}", i, 0);
			ft_splittrim_quotes(comm);
			ft_test_showsplit(comm, "()", i, 0);
			ft_split_free(comm);
			i++;
		}
		ft_split_free(pipe);
		line = get_next_line(ft_printf("$%s> ", s) * (long)ft_free(line));
	}
	ft_printf("done testing %s", s, ft_free(line));
}

static void	ft_test_showsplit(char **split, char *d, char n, int i)
{
	if (!split && n >= 0)
		ft_printf("null from %c", n + 'a');
	if (split && n >= 0)
		ft_printf("%c", n + 'a');
	while (split && split[i])
	{
		if (!ft_strcmp(d, "[]"))
			n = i + 'a';
		else
			n = i + '0';
		ft_printf("%c%c%s%c", n, d[0], split[i], d[1]);
		i++;
	}
	if (split)
		ft_printf("\n");
}

/*
//s = "something";
//o = "option=";
static void	ft_test_something(char *line, char *arg, char *s, char *o)
{
	line = get_next_line(0 * ft_printf("\ntesting %s :)\n$%s> ", s, s));
	arg = ft_strdup("+");
	while (ft_strcmp(line, "done"))
	{
		if (!ft_strncmp(line, o, ft_strlen(o)))
			arg = ft_strdup(line + ft_strlen(o) + (long)ft_free(arg));
		else
		{
			ft_printf("'%s' with %s'%s'\n", line, o, arg);
		}
		line = get_next_line(ft_printf("$%s> ", s) * (long)ft_free(line));
	}
	ft_printf("done testing %s", s, ft_free(arg), ft_free(line));
}
*/
