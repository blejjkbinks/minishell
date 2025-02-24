/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:47:04 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/19 18:47:06 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_split_debug(char **split, char *msg)
{
	int	i;

	if (!MS_DEBUG)
		return ;
	printf("MS_DEBUG: SPLIT_%s: ", msg);
	if (!split)
		printf("split is null");
	i = 0;
	while (split && split[i])
	{
		printf("[%s]", split[i]);
		i++;
	}
	printf(":)\n");
}

void	ft_pidfd_debug(char **split, int *pidfd)
{
	int	i;

	if (!MS_DEBUG || !split)
		return ;
	printf("MS_DEBUG: PIDFD: ");
	i = 0;
	while (split && split[i])
	{
		printf("[%d={pid:'%d'},", i, pidfd[N * i]);
		printf("{%d:'%d'}", N * i + 1, pidfd[N * i + 1]);
		printf("{%d:'%d'}]", N * i + 2, pidfd[N * i + 2]);
		i++;
	}
	printf("\n");
}

void	ft_str_debug(char *str, char *msg)
{
	if (!MS_DEBUG)
		return ;
	printf("MS_DEBUG: STR: %s: '(%s)'\n", msg, str);
}

void	ft_dup_debug(int a, int b, char *msg)
{
	if (!MS_DEBUG)
		return ;
	printf("MS_DEBUG: DUP2: %s, '%d'->'%d'\n", msg, a, b);
}
