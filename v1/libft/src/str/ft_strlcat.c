/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:56:01 by rdomange          #+#    #+#             */
/*   Updated: 2024/03/21 18:28:38 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t maxlen)
{
	size_t	dstlen;
	size_t	srclen;

	if (!dst || !src)
		return (0);
	dstlen = ft_strnlen(dst, maxlen);
	srclen = ft_strlen(src);
	if (dstlen == maxlen)
		return (maxlen + srclen);
	if (srclen < maxlen - dstlen)
		ft_strlcpy(dst + dstlen, src, srclen + 1);
	else
		ft_strlcpy(dst + dstlen, src, maxlen - dstlen);
	return (dstlen + srclen);
}
