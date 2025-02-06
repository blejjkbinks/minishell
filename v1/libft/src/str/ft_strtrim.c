/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:51:19 by rdomange          #+#    #+#             */
/*   Updated: 2024/03/28 16:03:24 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *str, const char *set)
{
	size_t	start;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len == 0)
		return (ft_strdup(""));
	while ((ft_strchr(set, str[len]) || str[len] == 0) && len > 0)
		len--;
	start = 0;
	while (ft_strchr(set, str[start]))
		start++;
	len -= start;
	return (ft_substr(str, start, len + 1));
}
