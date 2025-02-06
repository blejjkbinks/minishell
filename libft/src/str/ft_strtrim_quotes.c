/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 23:09:33 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/05 23:09:44 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	quoted(char c, int *q)
{
	int	prev;

	prev = *q;
	if (c == '\'' || c == '\"')
	{
		if (!*q)
			*q = c;
		else if (c == *q)
			*q = 0;
	}
	return (prev != *q);
}

void	ft_strtrim_quotes(char *str)
{
	int	i;
	int	j;
	int	q;

	if (!str)
		return ;
	i = 0;
	j = 0;
	q = 0;
	while (str && str[i])
	{
		if (!quoted(str[i], &q))
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
}
