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

void	init_minishell(char **env[3], char **envp_main, char **cash_question);
char	*get_prompt(char *prompt, char **env, int cash_question);

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*prompt;
	char	*cash_question;
	//char	*last_command;	//char	*line[4] : input, $?, !!
	char	**env[3];

	if (argc == 1)
		init_minishell(env, envp, &cash_question);
	while (argc == 1 && argv[0])
	{
		prompt = get_prompt(prompt, env[0], ft_atoi(cash_question));
		input = readline(prompt);
		if (strlen(input))
		{
			add_history(input);
			letsgo(input, env, &cash_question);
		}
		else
		{
			free(cash_question);
			cash_question = ft_itoa(0);
		}
		if (!input && MS_CUTE)
			return (0 + (0 * ft_printf("ctrl+d\n")));
		free(input);
	}
	return (0 * ft_printf("usage: ./minishell [script]\n"));
}

void	init_minishell(char **env[3], char **envp_main, char **cash_question)
{
	char	*str;

	//init_signals();
	if (MS_CUTE)
		ft_printf("(✿ ◕‿ ◕) hi~~ welcome to minishell (っ＾▿＾)っ\n");
	env[0] = ft_env_dup(envp_main);
	env[0] = ft_export(env[0], "OLDPWD=");
	env[1] = ft_split("yea=YEAAA,extra=EXXXTRA", ",");
	str = ft_itoa(ft_atoi(ft_env_get(env[0], "SHLVL")) + 1);
	ft_env_set(env[0], "SHLVL", str);
	ft_free(str);
	*cash_question = ft_itoa(0);
	//last_command = ft_strdup("U+00A1 U+00A1");
}

char	*get_prompt(char *prompt, char **env, int cash_question)
{
	char	*ret;
	char	*pwd;
	//add $USER
	ft_free(prompt);
	if (!MS_CUTE)
		return (ft_strdup("minishell$ "));
	pwd = ft_getcwd();
	if (ft_strchr(pwd, '/') == ft_strrchr(pwd, '/'))
		ret = ft_strjoin("minishell$ ", pwd);
	else if (!ft_strncmp(pwd, ft_env_get(env, "HOME"), ft_strlen(pwd) + 1))
		ret = ft_strdup("minishell$ ~");
	else
		ret = ft_strjoin("minishell$ ./", ft_strrchr(pwd, '/') + 1);
	free(pwd);
	if (cash_question == 0)
		pwd = ft_strjoin(ret, " " CLR_GRN ":3" CLR_RST " $ ");
	else
		pwd = ft_strjoin(ret, " " CLR_RED ":(" CLR_RST " $ ");
	free(ret);
	return (pwd);
}

void	letsgo()
{

}