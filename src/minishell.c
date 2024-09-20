/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:59:41 by rdomange          #+#    #+#             */
/*   Updated: 2024/09/19 20:00:25 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_prompt(void)
{
	return (ft_strdup("minishell$ "));
}

int	main(int argc, char **argv, char **envp_main)
{
	char	*line;
	char	*prompt;
	char	**env;

	if (argc == 1)
	{
		env = ft_env_dup(envp_main);
		(void)env;
	}
	while (argc == 1)
	{
		prompt = ft_get_prompt();
		line = readline(prompt);
		free(prompt);
		if (ft_strlen(line))
			ft_printf("%s.\n", line);
		if (line)
			free(line);
	}
	return (0 * ft_printf("usage: %s\n", argv[0]));
}
