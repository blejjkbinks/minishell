/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:33:57 by rdomange          #+#    #+#             */
/*   Updated: 2024/04/02 23:54:43 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i += ft_putchar_fd(str[i], fd);
	else
		return (ft_putstr_fd("(null)", fd));
	return (i);
}
