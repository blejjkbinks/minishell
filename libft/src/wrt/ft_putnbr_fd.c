/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:37:10 by rdomange          #+#    #+#             */
/*   Updated: 2024/04/07 20:35:00 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(long nbr, int fd)
{
	int	len;

	if (nbr == LONG_MIN)
		return (ft_putstr_fd("-9223372036854775807", fd));
	if (nbr == 0)
		return (ft_putstr_fd("0", fd));
	len = 0;
	if (nbr < 0)
	{
		len += ft_putstr_fd("-", fd);
		nbr *= -1;
	}
	if (nbr > 9)
		len += ft_putnbr_fd(nbr / 10, fd);
	len += ft_putchar_fd((char)(nbr % 10) + '0', fd);
	return (len);
}
