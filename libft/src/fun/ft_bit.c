/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 00:59:14 by rdomange          #+#    #+#             */
/*   Updated: 2024/08/15 00:59:27 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_bit(void *ptr, int i, int val)
{
	int		bsize;
	int		ret;
	char	*arr;

	arr = (char *)ptr;
	if (!arr)
		return (-1);
	ret = 3;
	bsize = sizeof(char) * 8;
	if (val == 0)
		arr[i / bsize] &= ~(1 << (i % bsize));
	else if (val == 1)
		arr[i / bsize] |= (1 << (i % bsize));
	else if (val == 2)
		ret = (arr[i / bsize] & (1 << (i % bsize))) != 0;
	else
		return (-2);
	return (ret);
}
