/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 06:05:43 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/07 16:28:50 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_split_quotes_count(const char *str, char d);
static char	*ft_split_quotes_word(const char *str, int *i, char d);
static int	ft_split_quotes_wordlen(const char *str, int start, char d);

char	**ft_split_quotes(const char *str, char d)
{
	char	**ret;
	int		count;
	int		i;
	int		k;

	count = ft_split_quotes_count(str, d);
	if (!count)
		return (NULL);
	ret = (char **)ft_calloc(count + 1, sizeof(char *));
	i = 0;
	k = 0;
	while (k < count)
	{
		while (str[i] == d)
			i++;
		ret[k] = ft_split_quotes_word(str, &i, d);
		if (!ret[k])
			return (ft_split_free(ret));
		k++;
	}
	ret[k] = NULL;
	return (ret);
}

static int	ft_split_quotes_count(const char *str, char d)
{
	int	i;
	int	count;
	int	in;
	int	q;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	in = 0;
	q = 0;
	while (str[i])
	{
		ft_isquoted(str[i], &q);
		if ((str[i] != d || q) && !in)
		{
			count++;
			in = 1;
		}
		else if (str[i] == d && !q)
			in = 0;
		i++;
	}
	return (count);
}

static char	*ft_split_quotes_word(const char *str, int *i, char d)
{
	char	*word;
	int		len;
	int		j;
	int		q;

	len = ft_split_quotes_wordlen(str, *i, d);
	if (!len)
		return (NULL);
	q = 0;
	j = 0;
	word = (char *)ft_malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (str[*i] && (str[*i] != d || q))
	{
		ft_isquoted(str[*i], &q);
		word[j++] = str[(*i)++];
	}
	word[j] = 0;
	return (word);
}

static int	ft_split_quotes_wordlen(const char *str, int start, char d)
{
	int	len;
	int	q;

	len = 0;
	q = 0;
	while (str[start] && (str[start] != d || q))
	{
		ft_isquoted(str[start], &q);
		len++;
		start++;
	}
	return (len);
}
