/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:45:03 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/18 14:45:04 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe_content(char *input, int i, int has_command);

int	invalid_pipe(char *input)
{
	int	has_command;
	int	i;

	i = 0;
	has_command = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (check_pipe_content(input, i, has_command))
				return (1);
			has_command = 0;
		}
		else if (!ft_isspace(*input))
			has_command = 1;
		i++;
	}
	return (0);
}

static int	check_pipe_content(char *input, int i, int has_command)
{
	if (!has_command)
	{
		printf("minishell: invalid token '|'\n");
		return (1);
	}
	i++;
	while (input[i] && ft_isspace(input[i]))
		i++;
	if (input[i] == '\0')
	{
		printf("minishell: invalid token '|'\n");
		return (1);
	}
	return (0);
}
//printf("Pipe '|' must be followed by a command\n");
//printf("Pipe '|' must be preceded by a command\n");