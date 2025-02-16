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

//char **cash_money(pipe[i], env, cash_question, last_command);
//also does split and trim_quotes at the end

char	*cash_get_var(char *str, int *i, char ***env);
char	*cash_get_other(char *str, int *i, char *cash_q, char *last_c);
char	*cash_malloc(char *str, char ***env, char *cash_q, char *last_c);

char	**cash_money(char *str, char ***env, char *cash_q, char *last_c)
{
	char	*ret;
	char	*var;
	int		i;
	int		j;
	int		q;
	char	**split;

	var = NULL;
	i = 0;
	j = 0;
	q = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '#')
		return (ft_free(str));
	ret = cash_malloc(str, env, cash_q, last_c);
	while (str && str[i])
	{
		ft_isquoted(str[i], &q);
		if (q != '\'')
			var = cash_get_var(str, &i, env);
		if (q != '\'' && !var)
			var = cash_get_other(str, &i, cash_q, last_c);
		if (var)
			j += ft_strlcat(ret, var, ft_strlen(ret) + ft_strlen(var) + 1);
		else
			ret[j++] = str[i++];
		var = ft_free(var);
	}
	//
	ft_printf("after cash_money:'%s'\n", ret);
	//
	split = ft_split_quotes(ret, ' ') + (long)ft_free(ret);
	ft_splittrim_quotes(split);
	return (split);
}

char	*cash_get_var(char *str, int *i, char ***env)
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
	if (str[*i] == '~' && (*i == 0 || str[*i - 1] == ' '))
		if (str[*i + 1] == 0 || str[*i + 1] == ' ' || str[*i + 1] == '/')
		{
			*i += 1;
			return (ft_strdup(ft_env_get(env[0], "HOME")));
		}
	return (NULL);
}

char	*cash_get_other(char *str, int *i, char *cash_q, char *last_c)
{
	if (!ft_strncmp(&str[*i], "$?", 2))
	{
		*i += 2;
		return (ft_strdup(cash_q));
	}
	if (str[*i] == '!' && str[*i + 1] == '!' && str[*i + 2] != '!')
		if (*i == 0 || str[*i - 1] != '!')
		{
			i += 2;
			return (ft_strdup(last_c));
		}
	return (NULL);
}

char	*cash_malloc(char *str, char ***env, char *cash_q, char *last_c)
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
			var = cash_get_var(str, &i, env);
		if (q != '\'' && !var)
			var = cash_get_other(str, &i, cash_q, last_c);
		if (var)
			j += ft_strlen(var);
		else
		{
			j++;
			i++;
		}
		var = ft_free(var);
	}
	return ((char *)ft_malloc((j + 1) * sizeof(char)));
}
