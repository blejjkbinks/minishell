/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_trim_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:09:14 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/07 15:13:21 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_split_trim_quotes(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		ft_strtrim_quotes(split[i]);
		i++;
	}
}
