/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:07:16 by rdomange          #+#    #+#             */
/*   Updated: 2024/03/19 21:59:31 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;

	if (!str)
		return (NULL);
	if ((char)c == 0)
		return ((char *)(str + ft_strlen(str)));
	i = ft_strlen(str);
	while (i > 0)
	{
		i--;
		if (str[i] == (char)c)
			return ((char *)(&str[i]));
	}
	return (NULL);
}
