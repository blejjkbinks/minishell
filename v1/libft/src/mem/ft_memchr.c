/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:34:55 by rdomange          #+#    #+#             */
/*   Updated: 2024/03/14 13:31:59 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t len)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)&(((char *)s)[i]));
		i++;
	}
	return (NULL);
}
