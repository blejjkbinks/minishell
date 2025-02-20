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
		e = find_redirection(pipe[i], &pidfd[(3 * i) + 1], &pidfd[(3 * i) + 2]);
		if (e)
		{
			if (e == 258)
				ft_printf("minishell: invalid token ><\n");
			*pidfd = e;
			return (e);
		}
		i++;
	}
	return (0);
}
