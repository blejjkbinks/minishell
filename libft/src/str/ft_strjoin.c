/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:35:26 by rdomange          #+#    #+#             */
/*   Updated: 2024/03/24 19:34:37 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*ret;
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	ret = (char *)ft_malloc((s1len + s2len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, s1len + 1);
	ft_strlcat(ret, s2, s1len + s2len + 1);
	return (ret);
}
