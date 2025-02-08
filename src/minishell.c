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
void	letsgo(char *input, char ***env, char **cash_question, char **last_command);

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*prompt;
	char	*cash_question;
	char	*last_command;
	char	***env;

	if (argc == 1)
		prompt = init_minishell(&env, envp, &cash_question, &last_command);
	while (argc == 1 && argv[0])
	{
		prompt = get_prompt(prompt, env[0], ft_atoi(cash_question));
		input = readline(prompt);
		if (ft_strlen(input))
			letsgo(input, env, &cash_question, &last_command);
		else
			cash_question = ft_itoa(0 + (long)ft_free(cash_question));
		if (!input && MS_CUTE)
			return (0 + (0 * ft_printf("ctrl+d message\n")));
		ft_free(input);
	}
	exit(0 * ft_printf("usage: ./minishell [script]\n"));
}

void	letsgo(char *input, char ***env, char **cash_question, char **last_command)
{
	char	**pipe;
	char	**comm;
	pid_t	*pid;	
	int		i;	//move deeper, 2 functions for pipe loop and wait loop
	int		s;	//minimum depth: needed in pipe loop, wait loop and cleanup

	add_history(input);
	pipe = ft_split_quotes(input, '|');
	pid = (pid_t *)ft_malloc(ft_split_len(pipe) * sizeof(pid_t));
	i = 0;
	while (pipe && pipe[i])
	{
		comm = ft_split_quotes(pipe[i], ' ');
		//redirection
		//cash_money
		if (!pipe[1] && ft_isbuiltin(comm[0]) > 1)
			s = ft_exec_builtin(comm, env);
		else
			ft_exec_pipe(comm, env, &pid[i]);
		ft_split_free(comm);
		i++;
	}
	i = 0;
	while (pipe && pipe[i])
	{
		if (pid[i] > 0)
			waitpid(pid[i], &s, 0);
		i++;
	}
	*cash_question = ft_itoa(((s & 0xff00) >> 8) + (long)ft_free(*cash_question));
	ft_split_free(pipe);
	ft_free(pid);
	return ;
	ft_printf("%s", *last_command);
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
	(*env)[1] = NULL;
	(*env)[2] = NULL;
	str = ft_itoa(ft_atoi(ft_env_get((*env)[0], "SHLVL")) + 1);
	(*env)[0] = ft_export((*env)[0], "SHLVL=");
	ft_env_set((*env)[0], "SHLVL", str);
	ft_free(str);
	*cash_question = ft_itoa(0);
	*last_command = ft_strdup("??");
	return (NULL);
}
