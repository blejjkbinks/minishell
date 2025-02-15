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

char	*cash_money(char *comm, char ***env, char *cash_q, char *last_c)
{
	char	*ret;
	int		i;

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
