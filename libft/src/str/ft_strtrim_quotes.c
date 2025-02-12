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

int	ft_strtrim_quotes(char *str)
{
	int	i;
	int	j;
	int	q;

	if (!str)
		return (-1);
	i = 0;
	j = 0;
	q = 0;
	while (str && str[i])
	{
		if (!ft_isquoted(str[i], &q))
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (q);
}
