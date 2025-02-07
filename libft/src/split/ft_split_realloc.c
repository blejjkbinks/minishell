/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_realloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:55:48 by rdomange          #+#    #+#             */
/*   Updated: 2024/09/30 15:55:50 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split_realloc(char **split, size_t new, size_t *cap_ptr)
{
	char	**ret;
	int		i;

	if (!split)
		return (NULL);
	ret = (char **)ft_malloc(new * sizeof(char *));
	i = 0;
	while (split[i])
	{
		ret[i] = split[i];
		i++;
	}
	ret[i] = NULL;
	ft_free(split);
	if (cap_ptr)
		*cap_ptr = new;
	return (ret);
}
