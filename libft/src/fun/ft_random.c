/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:26:19 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/13 15:26:20 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_random(void)
{
	static int	seed;
	int			*noise[10];
	int			i;

	if (!seed)
	{
		seed ^= (unsigned int)(size_t)(&seed);
		i = 0;
		while (i < 10)
		{
			noise[i] = (int *)ft_malloc(1 * sizeof(int));
			seed ^= (unsigned int)(size_t)(noise[i]);
			i++;
		}
		while (i--)
			ft_free(noise[i]);
	}
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return (seed);
}
