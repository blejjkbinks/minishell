/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:04:23 by rdomange          #+#    #+#             */
/*   Updated: 2024/09/20 18:04:25 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_quotes(char *str, char d)
{
	char	**ret;
	int		i;
	int		j;
	int		k;
	size_t	cap;
	size_t	cap2;
	char	quote;

	i = 0;	//str
	j = 0;	//copied str
	k = 0;	//index in array
	cap2 = DEFAULT_CAP;
	quote = 0;
	ret = (char **)ft_malloc(cap2 * sizeof(char *));
	while (str && str[i])
	{
		while (str[i] == ' ' || str[i] == d)
			i++;
		cap = DEFAULT_CAP;
		if (str[i])
			ret[k] = (char *)ft_malloc(cap * sizeof(char));
		j = 0;
		while (str[i] && (str[i] != d || quote))
		{
			if ((d == '|' && quoted(str[i], &quote) + 1) || (d == ' ' && !quoted(str[i], &quote)))
				ret[k][j++] = str[i];
			ret[k][j] = 0;
			if (j + 1 == (int)cap)
				ret[k] = ft_realloc(ret[k], j, cap * 2, &cap);
			i++;
		}
		ret[++k] = NULL;
		if (k + 1 == (int)cap2)
			ret = ft_split_realloc(ret, cap2 * 2, &cap2);
	}
	if (quote && d == '|')
		ft_printf("minishell: unclosed quote haha\n");
	return (ret);
}

char	***ft_split_triple(char *line)
{
	char	***ret;
	char	**first;
	int		i;

	first = ft_split_quotes(line, '|');
	ret = (char ***)malloc((ft_split_len(first) + 1) * sizeof(char **));
	i = 0;
	while (first[i])
	{
		ret[i] = ft_split_quotes(first[i], ' ');
		i++;
	}
	ret[i] = NULL;
	ft_split_free(first);
	return (ret);
}

void	ft_free_triple(char ***triple)
{
	int	i;
	int	j;

	i = 0;
	while (triple && triple[i])
	{
		j = 0;
		while (triple[i][j])
		{
			free(triple[i][j]);
			j++;
		}
		free(triple[i]);
		i++;
	}
	free(triple);
}
