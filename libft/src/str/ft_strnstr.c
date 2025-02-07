/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:14:38 by rdomange          #+#    #+#             */
/*   Updated: 2024/03/20 14:43:34 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	if (!find || find[0] == 0)
		return ((char *)str);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (str[i + j] == find[j])
		{
			j++;
			if (find[j] == 0)
				return ((char *)&str[i]);
			if (i + j == len || str[i + j] == 0)
				return (NULL);
		}
		if (str[i] == 0)
			return (NULL);
		i++;
	}
	return (NULL);
}
