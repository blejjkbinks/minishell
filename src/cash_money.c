/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cash_money.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:47:30 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/10 18:47:47 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cash_get_var(char *str, int *i, char ***env, char *cash_q);
static char	*cash_malloc(char *str, char ***env, char *cash_q);

char	*cash_money(char *str, char ***env, char *cash_q)
{
	char	*ret;
	char	*var;
	int		i;
	int		j;
	int		q;

	var = NULL;
	i = 0;
	j = 0;
	q = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '#')
		return (NULL);
	ret = cash_malloc(str, env, cash_q);
	while (str && str[i])
	{
		ft_isquoted(str[i], &q);
		if (q != '\'')
			var = cash_get_var(str, &i, env, cash_q);
		if (var)
		{
			ft_strlcat(ret, var, ft_strlen(ret) + ft_strlen(var) + 1);
			j += ft_strlen(var);
		}
		if (!var)
			ret[j++] = str[i++];
		var = ft_free(var);
	}
	return (ret);
}

static char	*cash_get_var(char *str, int *i, char ***env, char *cash_q)
{
	char	*ret;
	int		len;

	len = ft_env_name(str, NULL);
	if (*i == 0 && ft_env_get(env[2], str) && (str[len] == ' ' || !str[len]))
	{
		*i += len;
		return (ft_strdup(ft_env_get(env[2], str)));
	}
	if (str[*i] == '$' && ft_env_name(&str[*i + 1], NULL))
	{
		*i += 1;
		ret = ft_env_get(env[0], &str[*i]);
		if (!ret)
			ret = ft_env_get(env[1], &str[*i]);
		if (!ret)
			ret = "";
		*i += ft_env_name(&str[*i], NULL);
		return ft_strdup(ret);
	}
	if ((str[*i] == '~' && (*i == 0 || str[*i - 1] == ' ')) && \
		(str[*i + 1] == 0 || str[*i + 1] == ' ' || str[*i + 1] == '/'))
	{
		*i += 1;
		return (ft_strdup(ft_env_get(env[0], "HOME")));
	}
	if (!ft_strncmp(&str[*i], "$?", 2))
	{
		*i += 2;
		return (ft_strdup(cash_q));
	}
	return (NULL);
}

static char	*cash_malloc(char *str, char ***env, char *cash_q)
{
	int		i;
	int		j;
	int		q;
	char	*var;

	i = 0;
	j = 0;
	q = 0;
	var = NULL;
	while (str && str[i])
	{
		ft_isquoted(str[i], &q);
		if (q != '\'')
			var = cash_get_var(str, &i, env, cash_q);
		if (var)
			j += ft_strlen(var);
		else
		{
			j++;
			i++;
		}
		var = ft_free(var);
	}
	return ((char *)ft_calloc(j + 1, sizeof(char)));
}
