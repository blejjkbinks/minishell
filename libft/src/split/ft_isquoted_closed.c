/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isquoted_closed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:47:59 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/13 14:49:32 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isquoted_closed(const char *str)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (str && str[i])
	{
		ft_isquoted(str[i], &q);
		i++;
	}
	return (q);
}
