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

char	**ft_split_quotes_uhh(char *str)
{
	return (ft_split(str, " "));
}

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
			if (!quoted(str[i], &quote))
			{
				ret[k][j] = str[i];
				ret[k][++j] = 0;
			}
			i++;
			if (j + 1 == (int)cap)
				ret[k] = ft_realloc(ret[k], j, cap * 2, &cap);
		}
		ret[++k] = NULL;
		if (k + 1 == (int)cap2)
			ret = ft_split_realloc(ret, cap2 * 2, &cap2);
	}
	if (quote && d == '|')
		ft_printf("minishell: unclosed quote haha\n");
	return (ret);
}