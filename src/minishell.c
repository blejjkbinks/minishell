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
char	*get_prompt(char **prompt, char **env, int cash_question);
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
		input = readline(get_prompt(&prompt, env[0], ft_atoi(cash_question)));
		if (ft_strlen(input))
			letsgo(input, env, &cash_question, &last_command);
		else
			cash_question = ft_itoa(0 + *((int *)ft_free(cash_question)));
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

void	*init_minishell(char **env[3], char **envp_main, char **cash_question, char **last_command)
{
	char	*str;

	//init_signals();
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


//	minishell$ user@./pwd :3 $ 

char	*get_prompt(char **prompt, char **env, int cash_question)
{
	char	*pwd;
	char	*d[7];

	if (!MS_CUTE)
		return ("minishell$ ");
	pwd = ft_getcwd();
	d[0] = "minishell$ ";
	d[1] = ft_env_get(env, "USER");
	d[2] = "@ ./";
	if (ft_strchr(pwd, '/') == ft_strrchr(pwd, '/'))
		d[3] = pwd;
	else if (!ft_strcmp(pwd, ft_env_get(env, "HOME")))
		d[3] = "~";
	else
		d[3] = ft_strrchr(pwd, '/') + 1;
	d[4] = " ";
	if (cash_question == 0)
		d[5] = CLR_GRN ":3" CLR_RST;
	else
		d[5] = CLR_RED ":(" CLR_RST;
	d[6] = " $ ";
	cash_question = (ft_free(pwd) == ft_free(*prompt));
	*prompt = ft_strnjoin(7, d[0], d[1], d[2], d[3], d[4], d[5], d[6]);
	return (*prompt);
}
