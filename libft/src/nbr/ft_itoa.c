/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:01:06 by rdomange          #+#    #+#             */
/*   Updated: 2024/04/16 11:22:51 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(long nbr)
{
	size_t	len;
	char	*ret;

	if (nbr == 0)
		return (ft_strdup("0"));
	if (nbr == LONG_MIN)
		return (ft_strdup("-9223372036854775808"));
	len = ft_nbrlen(nbr);
	ret = (char *)ft_malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ret[len] = 0;
	if (nbr < 0)
	{
		ret[0] = '-';
		nbr *= -1;
	}
	while (nbr)
	{
		len--;
		ret[len] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (ret);
}
