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

int	double_exclam(char *str, int i)
{
	if (!(str[i] == '!' && str[i + 1] == '!' && str[i + 2] != '!'))
		return (0);
	if (!(!i || str[i - 1] != '!'))
		return (0);
	return (1);
}

char	*cash_money(t_mshl k)
{
	char	*ret;
	char	*var;
	int		len;
	int		i;
	size_t	cap;
	char	quote;

	quote = 0;
	cap = DEFAULT_CAP;
	ret = (char *)ft_calloc(cap, sizeof(char));
	len = 0;
	i = 0;
	while (k.line && k.line[i])
	{
		var = NULL;
		quoted(k.line[i], &quote);
		if (k.line[i] == '$' && ft_env_namelen(&k.line[i + 1]) && quote != '\'')
		{
			var = ft_env_get(k.env, &k.line[i + 1]);
			if (!var)
				var = ft_env_get(k.env_extra, &k.line[i + 1]);
			if (!var)
				var = "";
			i += ft_env_namelen(&k.line[i + 1]) + 1;
		}
		else if (!ft_strncmp(&k.line[i], "$?", 2) && quote != '\'')
		{
			var = k.exit_status;
			i += 2;
		}
		else if (tilda(&k.line[i], len, quote))
		{
			var = ft_env_get(k.env, "HOME");
			i += 1;
		}
		else if (double_exclam(k.line, i))
		{
			var = k.last_command;
			i += 2;
		}
		while (len + ft_strlen(var) + 1 >= cap)
			ret = ft_realloc(ret, len, cap * 2, &cap);
		if (var)
			len = ft_strlcat(ret, var, ft_strlen(ret) + ft_strlen(var) + 1);
		else
			ret[len++] = k.line[i++];
		ret[len] = 0;
	}
	return (ret);
}