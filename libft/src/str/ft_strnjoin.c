/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:44:09 by rdomange          #+#    #+#             */
/*   Updated: 2024/10/02 16:50:30 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(int count, ...)
{
	va_list	ap;
	char	*ret;
	char	*tmp;
	char	*arg;

	if (count <= 0)
		return (NULL);
	ret = ft_strdup("");
	va_start(ap, count);
	while (count--)
	{
		arg = va_arg(ap, char *);
		if (arg)
		{
			tmp = ft_strjoin(ret, arg);
			ft_free(ret);
			ret = tmp;
		}
	}
	va_end(ap);
	return (ret);
}
