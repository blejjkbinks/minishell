/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:02:25 by rdomange          #+#    #+#             */
/*   Updated: 2024/03/19 16:07:05 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	if (!str)
		return (NULL);
	if ((char)c == 0)
		return ((char *)(str + ft_strlen(str)));
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)(&str[i]));
		i++;
	}
	return (NULL);
}
