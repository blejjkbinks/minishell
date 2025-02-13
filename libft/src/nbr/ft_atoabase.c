/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:00:49 by rdomange          #+#    #+#             */
/*   Updated: 2024/04/16 11:03:51 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long	ft_atoi_base(char *str, int base);
static int				char_to_digit(char c);
static char				*ft_itoa_base(unsigned long nbr, int base);
static char				*ft_itoa_base_rev(char buffer[], int len);

char	*ft_atoabase(char *str, int src_b, int dst_b)
{
	unsigned long	nbr;
	char			*ret;

	str = ft_strtolower(ft_strdup(str));
	nbr = ft_atoi_base(str, src_b);
	ret = ft_itoa_base(nbr, dst_b);
	ft_free (str);
	return (ret);
}

static unsigned long	ft_atoi_base(char *str, int base)
{
	unsigned long	res;
	int				sign;
	size_t			i;
	int				d;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = +1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	res = 0;
	while (str[i])
	{
		res *= base;
		d = char_to_digit(str[i]);
		if (d == -1 || d > base || base < 2)
			return (0);
		res += d;
		i++;
	}
	if (sign == -1)
		return ((unsigned int)(res * sign));
	return (res);
}

static int	char_to_digit(char c)
{
	char	*pos;
	char	*dict;

	dict = "0123456789abcdef";
	pos = ft_strchr(dict, c);
	if (pos)
		return ((int)(pos - dict));
	else
		return (-1);
}

static char	*ft_itoa_base(unsigned long nbr, int base)
{
	size_t	i;
	char	buffer[65];
	char	*dict;

	dict = "0123456789abcdef";
	if (nbr == 0 || base < 2 || base > 16)
		return (ft_strdup("0"));
	i = 0;
	while (nbr)
	{
		buffer[i] = dict[nbr % base];
		nbr /= base;
		i++;
	}
	return (ft_itoa_base_rev(buffer, i));
}

static char	*ft_itoa_base_rev(char buffer[], int len)
{
	char	*ret;
	size_t	i;

	ret = (char *)ft_malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (len)
	{
		len--;
		ret[i] = buffer[len];
		i++;
	}
	ret[i] = 0;
	return (ret);
}
