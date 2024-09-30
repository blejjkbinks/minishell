/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:04:23 by rdomange          #+#    #+#             */
/*   Updated: 2024/09/20 18:04:25 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_quotes(char *str)
{
	return (ft_split(str, " "));
}

char	**ft_split_quotesss(char *str)
{
	char	**ret;
	char	**tmp;
	int		i;
	int		len;
	size_t	cap;
	char	quote;

	ret = ft_env_dup(NULL);
	i = 0;
	len = 0;
	cap = 16;
	quote = 0;
	while (str && str[i])
	{
		
	}
	return (ret);
}