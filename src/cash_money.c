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

char	*cash_money(char *str, char ***env, char *cash_q, char *last_c)
{
	char	*ret;
	char	*var;
	int		i;
	int		j;
	int		q;

	//get len for malloc
	var = NULL;
	i = 0;
	j = 0;
	q = 0;
	while (str && str[i])
	{
		ft_isquoted(str[i], &q);
		if (q != '\'')
			var = cash_get_var(str, &i, env);
		if (q != '\'' && !var)
			var = cash_get_cash_q;
		if (q != '\'' && !var)
			var = cash_get_last_c;
		if (var)
			j += ft_strlcat();
		else
			ret[j++] = str[i++];
		var = ft_free(val);
	}
	return (ret);
}

char	*cash_get_var(char *str, int *i, char ***env, char *cash_q)
{
	char	*ret;

	ret = NULL;
	if (str[*i] == '$' && ft_env_name(str[*i + 1], NULL))
	{
		ret = ft_env_get(env[0], str[*i + 1]);
		if (!ret)
			ret = ft_env_get(env[1], str[*i + 1]);
		if (!ret)
			ret = "";
		*i += ft_env_name(str[*i + 1], NULL) + 1;
	}
	if (!ft_strncmp(str[*i], "$?", 2))
	{
		ret = cash_q;
		*i += 2;
	}
	if ("~")
	{
		ret = ft_env_get(env[0], "HOME");
		*i += 1;
	}
	if ("!!")
		ret = last_c;

	return (ft_strdup(ret));
}

//split and trim quotes here? and then return "char **comm"
/*{
	char	**ret;
	char	**alias;
	char	*str;
	int		len;
	int		i;

	if (comm[0][0] == '#')
		return (ft_split_free(comm));
	alias = ft_split_quotes(ft_env_get(env[2], comm[0]), ' ');
	len = ft_split_len(alias) + ft_split_len(comm) - (ft_split_len(alias) != 0);
	ret = (char **)ft_malloc((len + 1) * sizeof(char *));
	i = -1;
	while (alias && alias[++i])
		ret[i] = alias[i];
	j = (i != 0);
	ft_split_free(alias);
	while (comm && comm[j])
	{
		ret[i] = expand_line(comm[j], env, (i == 0));
		i++;
		j++;
	}
	ret[i] = NULL;
	ft_split_free(comm);
	return (ret);
}*/
