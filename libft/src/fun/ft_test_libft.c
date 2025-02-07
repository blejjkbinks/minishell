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

static void	ft_test_show_split(char **split, char *d, int step)
{
	int	i;

	if (step == 0)
		ft_printf("split_set with d='%s'\n", d);
	if (step == 1)
		ft_printf("split_quotes with d='%c'\n", d[0]);
	if (step == 2)
		ft_printf("trimming quotes\n");
	i = 0 * ft_printf("->");
	while (split[i])
	{
		if (step == 2)
			ft_strtrim_quotes(split[i]);
		ft_printf("%s", split[i]);
		if (split[i + 1])
			ft_printf(":");
		i++;
	}
	ft_printf(";");
	if (step != 2)
		ft_printf("\n");
	ft_split_free(split);
}

static void	ft_test_split(char *line)
{
	char	*d;

	ft_printf("\ntesting split :)");
	d = ft_strdup(" ");
	line = get_next_line(0 + (0 * ft_printf("\n> ")));
	while (TRUE)
	{
		while (!ft_strncmp(line, "d=", 2) && line[2])
		{
			ft_free(d);
			d = ft_strdup(line + 2);
			ft_free(line);
			line = get_next_line(0 + (0 * ft_printf("> ")));
		}
		if (!ft_strcmp(line, "done"))
			break ;
		ft_test_show_split(ft_split_set(line, d), d, 0);
		ft_test_show_split(ft_split_quotes(line, d[0]), d, 1);
		ft_test_show_split(ft_split_quotes(line, d[0]), d, 2);
		ft_free(line);
		line = get_next_line(0 + (0 * ft_printf("\n> ")));
	}
	ft_free(d);
	ft_free(line);
	ft_printf("done testing split, back to menu");
}

void	ft_test_libft(void)
{
	char	*line;

	ft_printf("testing libft:)");
	line = get_next_line(0 + (0 * ft_printf("\n> ")));
	while (ft_strcmp(line, "done"))
	{
		ft_printf("get_next_line got:'%s'", line);
		if (!ft_strcmp(line, "split"))
			ft_test_split(line);
		ft_free(line);
		line = get_next_line(0 + (0 * ft_printf("\n> ")));
	}
	ft_free(line);
	ft_printf("done testing");
}
