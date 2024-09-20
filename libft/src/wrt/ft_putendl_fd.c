/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:36:01 by rdomange          #+#    #+#             */
/*   Updated: 2024/04/02 23:30:44 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putendl_fd(char *str, int fd)
{
	size_t	len;

	len = 0;
	len += ft_putstr_fd(str, fd);
	len += ft_putstr_fd("\n", fd);
	return (len);
}
