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

void	cash_get_var(t_mshl *k)
{
	if (cash_get_var_line_too_long(k))
	{
		k->var = ft_env_get(k->env, &k->line[k->i + 1]);
		if (!k->var)
			k->var = ft_env_get(k->env_extra, &k->line[k->i + 1]);
		if (!k->var)
			k->var = "";
		k->i += ft_env_namelen(&k->line[k->i + 1]) + 1;
	}
	else if (!ft_strncmp(&k->line[k->i], "$?", 2) && k->quote != '\'')
	{
		k->var = k->exit_status;
		k->i += 2;
	}
	else if (tilda(&k->line[k->i], k->len, k->quote))
	{
		k->var = ft_env_get(k->env, "HOME");
		k->i += 1;
	}
	else if (double_exclam(k->line, k->i))
	{
		k->var = k->last_command;
		k->i += 2;
	}
}

char	*cash_money(t_mshl k)
{
	k.quote = 0;
	k.cap = DEFAULT_CAP;
	k.ret = (char *)ft_calloc(k.cap, sizeof(char));
	k.len = 0;
	k.i = 0;
	while (k.line && k.line[k.i])
	{
		k.var = NULL;
		quoted(k.line[k.i], &(k.quote));
		cash_get_var(&k);
		while (k.len + ft_strlen(k.var) + 1 >= k.cap)
			k.ret = ft_realloc(k.ret, k.len, k.cap * 2, &(k.cap));
		if (k.var)
			k.len = cash_money_line_too_long(k);
		else
			k.ret[k.len++] = k.line[k.i++];
		k.ret[k.len] = 0;
	}
	return (k.ret);
}
