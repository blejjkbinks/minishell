/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:28:18 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/05 17:06:21 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_split_alloc(const char *str, const char *d)
{
	size_t	i;
	size_t	words;
	char	**ret;

	if (!str)
		return (NULL);
	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && ft_strchr(d, str[i]))
			i++;
		if (str[i])
			words++;
		while (str[i] && !ft_strchr(d, str[i]))
			i++;
	}
	ret = (char **)ft_malloc((words + 1) * sizeof(char *));
	return (ret);
}

static	size_t	ft_split_wordlen(const char *str, const char *d)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && !ft_strchr(d, str[i]))
		i++;
	return (i);
}

char	**ft_split_set(const char *str, const char *d)
{
	char	**ret;
	size_t	i;
	size_t	len;

	ret = ft_split_alloc(str, d);
	if (!ret)
		return (NULL);
	i = 0;
	while (*str)
	{
		while (*str && ft_strchr(d, *str))
			str++;
		if (!*str)
			break ;
		len = ft_split_wordlen(str, d);
		ret[i] = ft_substr(str, 0, len);
		ret[i + 1] = NULL;
		if (!ret[i])
			return (ft_split_free(ret));
		str += len;
		i++;
	}
	return (ret);
}
