/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 06:05:43 by rdomange          #+#    #+#             */
/*   Updated: 2025/01/03 06:05:44 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split_quotes_word(const char *str, char **ret, char d, int i[6])
{
	i[1] = 0;
	while (str[i[0]] && (str[i[0]] != d || i[3]))
	{
		ft_isquoted(str[i[0]], &i[3]);
		ret[i[2]][i[1]++] = str[i[0]++];
		ret[i[2]][i[1]] = 0;
		if (i[1] + 1 == i[4])
			ret[i[2]] = ft_realloc(ret[i[2]], i[1], i[4] * 2, (size_t *)&i[4]);
	}
	ret[++i[2]] = NULL;
	if (i[2] + 1 == i[5])
		ret = ft_split_realloc(ret, i[5] * 2, (size_t *)&i[5]);
	return (ret);
}

char	**ft_split_quotes(const char *str, char d)
{
	char	**ret;
	int		i[6];

	ft_bzero(i, sizeof(i));
	i[5] = DEFAULT_CAP;
	ret = (char **)ft_malloc(i[5] * sizeof(char *));
	if (!ret)
		return (NULL);
	while (str && str[i[0]])
	{
		while (str[i[0]] == ' ' || str[i[0]] == d)
			i[0]++;
		i[4] = DEFAULT_CAP;
		if (str[i[0]])
			ret[i[2]] = (char *)ft_malloc(i[4] * sizeof(char));
		if (!ret[i[2]])
			return (ft_split_free(ret));
		ret = ft_split_quotes_word(str, ret, d, i);
		if (!ret)
			return (NULL);
	}
	return (ret);
}
