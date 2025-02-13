/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:25:33 by rdomange          #+#    #+#             */
/*   Updated: 2024/05/06 14:10:48 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_atoi_dec(const char *str);
static long	ft_atoi_hex(const char *s);

long	ft_atoi(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (!ft_strncmp("0x", &str[i], 2) || !ft_strncmp("0X", &str[i], 2))
		return (ft_atoi_hex(&str[i + 2]));
	else
		return (ft_atoi_dec(str));
}

static long	ft_atoi_dec(const char *str)
{
	long	ret;
	int		i;
	int		sign;

	if (!str)
		return (0);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = +1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	ret = 0;
	while (ft_isdigit(str[i]))
	{
		ret *= 10;
		ret += str[i] - '0';
		i++;
	}
	return (ret * sign);
}

static long	ft_atoi_hex(const char *s)
{
	int		i;
	long	ret;
	char	*dict;
	char	*str;

	i = 0;
	ret = 0;
	dict = "0123456789abcdef";
	str = ft_strdup(s);
	str = ft_strtolower(str);
	while (str[i] && ft_strchr(dict, str[i]))
	{
		ret *= 16;
		ret += ft_strchr(dict, str[i]) - dict;
		i++;
	}
	ft_free (str);
	return (ret);
}
