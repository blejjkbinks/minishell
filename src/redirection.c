/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:31:15 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/11 13:31:16 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection(char **pipe, int *pidfd)
{
	int	i;
	int	e;

	i = 0;
	while (pipe && pipe[i])
	{
		e = find_redirection(pipe[i], &pidfd[(N * i) + 1], &pidfd[(N * i) + 2]);
		if (e)
		{
			if (e == 258)
				ft_printf("minishell: invalid token >< >:(\n");
			*pidfd = e;
			return (e);
		}
		i++;
	}
	return (0);
}

void	redirection_close(char **pipe, int *pidfd)
{
	int	i;

	i = 0;
	while (pipe && pipe[i])
	{
		if (pidfd[(N * i) + 1])
			close(pidfd[(N * i) + 1]);
		if (pidfd[(N * i) + 2])
			close(pidfd[(N * i) + 2]);
		i++;
	}
}
