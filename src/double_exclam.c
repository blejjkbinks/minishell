/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_exclam.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 02:56:43 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/17 02:56:45 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*double_exclam_get(char *str, int *i, char *last_c);
static char	*double_exclam_alloc(char *str, char *last_c);
static void	double_exclam_print(char *str, int p);

char	*double_exclam(char *str, char *last_c)
{
	char	*ret;
	int		i;
	int		j;
	int		q;
	int		p;

	ret = double_exclam_alloc(str, last_c);
	i = 0;
	j = 0;
	q = 0;
	p = 0;
	while (str && str[i])
	{
		ft_isquoted(str[i], &q);
		if (!q && double_exclam_get(str, &i, last_c))
		{
			ft_strlcat(ret, last_c, ft_strlen(ret) + ft_strlen(last_c) + 1);
			j += ft_strlen(last_c);
			p++;
		}
		else
			ret[j++] = str[i++];
	}
	double_exclam_print(ret, p);
	return (ret);
}

static void	double_exclam_print(char *str, int p)
{
	if (p)
		ft_printf("!!:%s\n", str);
}

static char	*double_exclam_get(char *str, int *i, char *last_c)
{
	if ((str[*i] == '!' && str[*i + 1] == '!' && str[*i + 2] != '!') && \
		(*i == 0 || str[*i - 1] != '!'))
	{
		*i += 2;
		return (last_c);
	}
	return (NULL);
}

static char	*double_exclam_alloc(char *str, char *last_c)
{
	int	i;
	int	j;
	int	q;

	i = 0;
	j = 0;
	q = 0;
	while (str && str[i])
	{
		ft_isquoted(str[i], &q);
		if (!q && double_exclam_get(str, &i, last_c))
			j += ft_strlen(last_c);
		else
		{
			i++;
			j++;
		}
	}
	return ((char *)ft_calloc((j + 1), sizeof(char)));
}
