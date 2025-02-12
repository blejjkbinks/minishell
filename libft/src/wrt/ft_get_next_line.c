/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:50:15 by rdomange          #+#    #+#             */
/*   Updated: 2024/04/29 15:45:32 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	char	*ret;
	size_t	i;
	size_t	c;

	c = DEFAULT_CAP;
	i = 0;
	ret = (char *)ft_malloc(c * sizeof(char));
	while (ret && read(fd, &ret[i], 1) == 1)
	{
		if (ret[i] == '\n')
		{
			ret[i] = 0;
			return (ret);
		}
		ret[++i] = 0;
		if (i + 1 == c)
			ret = ft_realloc(ret, i, c * 2, &c);
	}
	if (!i)
		return (ft_free(ret));
	return (ret);
}
