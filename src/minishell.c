/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:37:58 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/06 14:38:08 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*init_minishell(char ****env, char **envp_main, char **cash_question, char **last_command);

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*prompt;
	char	*cash_question;
	char	*last_command;
	char	***env;

	prompt = init_minishell(&env, envp, &cash_question, &last_command);
	while (argc == 1)
	{
		prompt = get_prompt(prompt, env[0], ft_atoi(cash_question));
		input = readline(prompt);
		//input = get_next_line(0 * ft_printf("%s", prompt));
		if (ft_strlen(input))
			letsgo(input, env, &cash_question, &last_command);
		if (!input && MS_CUTE)
			exit(0 + (0 * ft_printf("( •_•) minishell ctrl+d'ed (´･_･`)\n")));
		free(input);
	}
	exit(1 + (0 * ft_printf("usage: %s\n", argv[0])));
}

//	init_signals();
void	*init_minishell(char ****env, char **envp_main, char **cash_question, char **last_command)
{
	char	*str;

	if (MS_CUTE)
		ft_printf("(✿ ◕‿ ◕) hi~~ welcome to minishell (っ＾▿＾)っ\n");
	*env = (char ***)ft_malloc(3 * sizeof(char **));
	(*env)[0] = ft_env_dup(envp_main);
	(*env)[0] = ft_export((*env)[0], "OLDPWD=");
	str = ft_itoa(ft_atoi(ft_env_get((*env)[0], "SHLVL")) + 1);
	(*env)[0] = ft_export((*env)[0], "SHLVL=");
	ft_env_set((*env)[0], "SHLVL", str);
	free(str);
	(*env)[1] = NULL;
	(*env)[2] = NULL;
	*cash_question = ft_itoa(0);
	*last_command = ft_strdup("??");
	return (NULL);
}
