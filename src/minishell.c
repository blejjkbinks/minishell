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

void	*init_minishell(char **env[3], char **envp_main, char **cash_question, char **last_command);
void	letsgo(char *input, char **env[3], char **cash_question, char **last_command);

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*prompt;
	char	*cash_question;
	char	*last_command;
	char	**env[3];

	if (argc == 1)
		prompt = init_minishell(env, envp, &cash_question, &last_command);
	while (argc == 1 && argv[0])
	{
		prompt = get_prompt(prompt, env[0], ft_atoi(cash_question));
		input = readline(prompt);
		if (ft_strlen(input))
			letsgo(input, env, &cash_question, &last_command);
		else if (!ft_free(cash_question))
			cash_question = ft_itoa(0);
		if (!input && MS_CUTE)
			return (0 + (0 * ft_printf("ctrl+d message\n")));
		free(input);
	}
	return (0 * ft_printf("usage: ./minishell [script]\n"));
}

void	letsgo(char *input, char **env[3], char **cash_question, char **last_command)
{
	add_history(input);
	ft_printf("in letsgoooo with '%s'\n", input);
	(void)env;
	(void)cash_question;
	(void)last_command;
}

//	init_signals();
void	*init_minishell(char **env[3], char **envp_main, char **cash_question, char **last_command)
{
	char	*str;

	if (MS_CUTE)
		ft_printf("(✿ ◕‿ ◕) hi~~ welcome to minishell (っ＾▿＾)っ\n");
	env[0] = ft_env_dup(envp_main);
	env[0] = ft_export(env[0], "OLDPWD=");
	env[1] = NULL;
	env[2] = NULL;
	str = ft_itoa(ft_atoi(ft_env_get(env[0], "SHLVL")) + 1);
	ft_env_set(env[0], "SHLVL", str);
	ft_free(str);
	*cash_question = ft_itoa(0);
	*last_command = ft_strdup("\xC2\xA1\xC2\xA1");
	return (NULL);
}
