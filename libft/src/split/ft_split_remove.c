/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:58:37 by rdomange          #+#    #+#             */
/*   Updated: 2024/10/02 16:59:04 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split_remove(char **split, int r)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (i == r)
		{
			ft_free(split[r]);
			while (split[i + 1])
			{
				split[i] = split[i + 1];
				i++;
			}
			split[i] = NULL;
			return (split);
		}
		i++;
	}
	return (split);
}
