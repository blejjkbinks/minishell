/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:07:06 by rdomange          #+#    #+#             */
/*   Updated: 2024/09/10 14:59:13 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_printf_elem(va_list *a, const char **fmt, char *e, int *flg);
static int	*ft_printf_getflg(va_list *a, const char **fmt, int *flg);
static char	*ft_printf_extend(char *e, int *flg, size_t p);
static char	*ft_printf_trans(char *e, char *f, int *flg, int base);

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	char	*str;
	int		len;
	int		flg[128];

	va_start(ap, fmt);
	len = 0;
	while (fmt && *fmt)
	{
		if (*fmt == '%' && *(fmt + 1) && *(++fmt))
		{
			str = ft_printf_elem(&ap, &fmt, NULL, flg);
			if (!str)
				break ;
			len += ft_putstr_fd(str, 1);
			if (flg['c'] && !ft_strcmp(str, "^@") && flg[1] < 2)
				len--;
			ft_free (str);
		}
		else if (*(fmt++))
			len += ft_putchar_fd(*(fmt - 1), 1);
	}
	va_end(ap);
	return ((len * (*fmt == 0)) + (-1 * (*fmt != 0)));
}

static char	*ft_printf_elem(va_list *a, const char **fmt, char *e, int *flg)
{
	flg = ft_printf_getflg(a, fmt, flg);
	if (!flg)
		return (NULL);
	if (flg['l'] && ft_strchr("uxXob", *flg))
		e = ft_itoa_ulong((unsigned long)va_arg(*a, long));
	if (flg['l'] && ft_strchr("di", *flg))
		e = ft_itoa(va_arg(*a, long));
	if ((!flg['l']) && ft_strchr("diuxXob", *flg))
		e = ft_itoa(va_arg(*a, int));
	if (ft_strchr("fF", *flg))
		e = ft_strdup(":)f to a F:)");
	if (ft_strchr("gG", *flg))
		e = ft_strdup(":)f to a G:)");
	if (*flg == 'p')
		e = ft_itoa_ulong((unsigned long)va_arg(*a, void *));
	if (*flg == 's')
		e = ft_strdup(va_arg(*a, char *));
	if (ft_strchr("c%", *flg))
		e = ft_strdup("%");
	if (*flg == 'c')
		*e = (char)va_arg(*a, int);
	return (ft_printf_trans(e, e, flg, 0));
}

static int	*ft_printf_getflg(va_list *a, const char **fmt, int *flg)
{
	ft_bzero(flg, 128 * sizeof(int));
	while (flg && ft_strchr("-+ 0'#", **fmt) && *(++(*fmt)))
		flg[(int)(*((*fmt) - 1))] = 1;
	while (flg && ft_isdigit(**fmt) && *(++(*fmt)))
		flg[1] = (flg[1] * 10) + (*((*fmt) - 1) - '0');
	if (flg && flg[1] == 0 && **fmt == '*' && *(++(*fmt)))
		flg[1] = va_arg(*a, int);
	if (flg && **fmt == '.' && *(++(*fmt)) && ++flg[3])
		while (ft_isdigit(**fmt) && *(++(*fmt)))
			flg[2] = (flg[2] * 10) + (*((*fmt) - 1) - '0');
	if (flg[2] == 0 && **fmt == '*' && *(++(*fmt)) && flg[3])
		flg[2] = va_arg(*a, int);
	if (**fmt == 'l' && *(++(*fmt)))
		flg['l']++;
	*flg = *((*fmt)++);
	if ((!ft_strchr("%cspdiuxXobfFgG", *flg)))
		return (NULL);
	return (flg);
}

static char	*ft_printf_trans(char *e, char *f, int *flg, int base)
{
	base += (2 * (*flg == 'b')) + (8 * (*flg == 'o')) + (10 * (*flg == 'u'));
	base += (16 * (ft_strchr("xXp", *flg) != NULL));
	if (base)
		e = ft_atoabase(e, 10, base);
	if (*flg == 's' && !e)
		e = ft_strdup("(null)");
	if (*flg == 'c' && *e == 0)
		e = ft_strdup("^@");
	if (f != e && f)
		ft_free (f);
	if (*flg == 'p' || (flg['#'] && ft_strchr("xX", *flg)))
		e = ft_strjoin_free("0x", e, 2);
	if (ft_isalpha_upper(*flg))
		ft_strtoupper(e);
	return (ft_printf_extend(e, flg, (size_t)flg[2]));
}

static char	*ft_printf_extend(char *e, int *flg, size_t p)
{
	if (p && *flg == 's' && ft_strlen(e) > p)
		e[p] = 0;
	if (p && ft_strchr("fF", *flg) && ft_strlen(ft_strchr(e, '.')) > p)
		e[(ft_strchr(e, '.') - e) + flg[2] + 1] = 0;
	if (ft_strchr("diouxX", *flg) && flg['+'] && !ft_strchr(e, '-'))
		e = ft_strjoin_free("+", e, 2);
	else if (ft_strchr("diouxX", *flg) && flg[' '] && !ft_strchr(e, '-'))
		e = ft_strjoin_free(" ", e, 2);
	while ((ft_strlen(e) + (flg[' '] || flg['+'])) < (size_t)flg[1])
	{
		if (flg['-'])
			e = ft_strjoin_free(e, " ", 1);
		else if (flg['0'] && ft_strchr("diouxX", *flg))
			e = ft_strjoin_free("0", e, 2);
		else
			e = ft_strjoin_free(" ", e, 2);
	}
	return (e);
}
