/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmemory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 21:43:29 by rdomange          #+#    #+#             */
/*   Updated: 2024/05/21 16:10:52 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printmemory_topaddress(void *p);
static void	ft_printmemory_putptr(void *p);
static void	ft_printmemory_hexcontent(void *p, size_t len, size_t start);
static void	ft_printmemory_chrcontent(void *p, size_t len, size_t start);

void	*ft_printmemory(void *ptr, size_t len)
{
	size_t	i;

	ft_printmemory_topaddress(ptr);
	i = 0;
	while (i < len)
	{
		ft_printmemory_putptr(ptr + i);
		ft_putstr_fd(": ", 1);
		ft_printmemory_hexcontent(ptr, len, i);
		ft_printmemory_chrcontent(ptr, len, i);
		ft_putstr_fd("\n", 1);
		i += 16;
	}
	return (ptr);
}

static void	ft_printmemory_topaddress(void *p)
{
	unsigned long	ptr;
	char			*dict;
	int				c;
	int				i;

	ptr = (unsigned long)p;
	dict = "0123456789abcdef";
	ft_putstr_fd("                    ", 1);
	i = 0;
	while (i < 16)
	{
		c = ((ptr + i) % 16);
		ft_putchar_fd(dict[c], 1);
		ft_putstr_fd(" ", 1);
		if (i % 2 == 1)
			ft_putstr_fd(" ", 1);
		i++;
	}
	ft_putstr_fd("                \n", 1);
}

static void	ft_printmemory_putptr(void *p)
{
	unsigned long	ptr;
	char			*dict;
	char			buffer[17];
	size_t			i;

	ptr = (unsigned long)p;
	dict = "0123456789abcdef";
	i = 0;
	while (i < 16)
	{
		buffer[i] = dict[ptr % 16];
		ptr /= 16;
		i++;
	}
	ft_putstr_fd("0x", 1);
	while (i > 0)
	{
		i--;
		ft_putchar_fd(buffer[i], 1);
	}
}

static void	ft_printmemory_hexcontent(void *p, size_t len, size_t start)
{
	unsigned char	*ptr;
	char			*dict;
	size_t			i;

	ptr = (unsigned char *)p;
	dict = "0123456789abcdef";
	i = 0;
	while (i < 16)
	{
		if (start + i >= len)
			ft_putstr_fd("  ", 1);
		else
		{
			ft_putchar_fd(dict[ptr[start + i] / 16], 1);
			ft_putchar_fd(dict[ptr[start + i] % 16], 1);
		}
		if (i % 2)
			ft_putstr_fd(" ", 1);
		i++;
	}
}

static void	ft_printmemory_chrcontent(void *p, size_t len, size_t start)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)p;
	i = 0;
	while (i < 16)
	{
		if (start + i >= len)
			ft_putstr_fd(" ", 1);
		else
		{
			if (!ft_isprint(ptr[start + i]))
				ft_putstr_fd(".", 1);
			else
				ft_putchar_fd(ptr[start + i], 1);
		}
		i++;
	}
}
