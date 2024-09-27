/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:45:50 by rdomange          #+#    #+#             */
/*   Updated: 2024/09/23 17:45:51 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quoted(char c, char *quote)
{
	char	prev;

	prev = *quote;
	if (c == '\'' || c == '\"')
	{
		if (!*quote)
			*quote = c;
		else if (c == *quote)
			*quote = 0;
	}
	return (prev != *quote);
}

int	tilda(char *str, int len, char quote)
{
	if (!(*str == '~' && !quote))
		return (0);
	if (!(*(str + 1) == 0 || *(str + 1) == ' ' || *(str + 1) == '/'))
		return (0);
	if (!(!len || *(str - 1) == ' '))
		return (0);
	return (1);
}

/*
static char	*dollar_tilda(char *str, char **env, char quote, int i, char *exit_status)
{
	char	*ret;

	if (*str == '~' && !quote)
		if (*(str + 1) == 0 || *(str + 1) == ' ' || *(str + 1) == '/')
			if (!i || *(str - 1) == ' ')
				return (ft_env_get(env, "HOME"));
	if (str[0] == '$' && str[1] == '?')
		return (exit_status);
	if (*str == '$' && quote != '\'')
		ret = ft_env_get(env, str + 1);
	if (!ret)
		ret = ft_env_get(env_extra, str + 1);
	if (!ret)
		ret = "";
	return (ret);
}*/

char	*cash_money(t_mshl k)
{
	char	*ret;
	char	*var;
	int		len;
	size_t	cap;
	char	quote;

	quote = 0;
	cap = 16;
	ret = (char *)ft_calloc(cap, sizeof(char));
	len = 0;
	while (k.line && *k.line)
	{
		var = NULL;
		quoted(*k.line, &quote);
		if (*k.line == '$' && ft_env_namelen(k.line + 1) && quote != '\'')
		{
			var = ft_env_get(k.env, k.line + 1);
			k.line += ft_env_namelen(k.line + 1) + 1;
		}
		else if (!ft_strncmp(k.line, "$? ", 3) && quote != '\'')
		{
			var = k.exit_status;
			k.line += 2;
		}
		else if (tilda(k.line, len, quote))
		{
			var = ft_env_get(k.env, "HOME");
			k.line += 1;
		}
		if (len + 1 + ft_strlen(var) >= cap)
			ret = ft_realloc(ret, len, cap + 1 + ft_strlen(var), &cap);
		if (var)
			len = ft_strlcat(ret, var, ft_strlen(ret) + ft_strlen(var));
		else
			ret[len++] = *k.line++;
		ret[len] = 0;
	}
	return (ret);
}