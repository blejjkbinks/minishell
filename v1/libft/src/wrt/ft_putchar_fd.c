/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:33:06 by rdomange          #+#    #+#             */
/*   Updated: 2024/05/21 16:12:57 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putchar_fd(char c, int fd)
{
	int	ret;

	ret = write(fd, &c, 1);
	if (ret == -1)
		return (0 * ft_putstr_fd(":( ft_putchar error :(\n", 1));
	return (ret);
}
