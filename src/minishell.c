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
void	letsgo_pipe(char **pipe, char ***env, char **cash_question, char **last_command);
void	letsgo_wait(int len, pid_t *pid, int status, char **cash_question);

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
		if (ft_strlen(input))
			letsgo(input, env, &cash_question, &last_command);
		else
			cash_question = ft_itoa(0 + (long)ft_free(cash_question));
		if (!input && MS_CUTE)
			exit(0 + (0 * ft_printf("ctrl+d message\n")));
		free(input);
	}
	if (argc == 2)
		exit(0 + (0 * ft_printf("go %s\n", argv[1])));
	exit(1 + (0 * ft_printf("usage: ./minishell [script]\n")));
}

void	letsgo(char *input, char ***env, char **cash_question, char **last_command)
{
	char	**pipe;
	char	*check_closed;

	add_history(input);
	check_closed = ft_strdup(input);
	if (ft_strtrim_quotes(check_closed))
	{
		if (MS_CUTE)
			ft_printf("minishell: unclosed quote >:(\n");
		*cash_question = ft_itoa(1 + (long)ft_free(*cash_question));
		return ;
	}
	//pipe = ft_split_quotes(input, '|');
	pipe = ft_split(input, '|');
	letsgo_pipe(pipe, env, cash_question, last_command);
	ft_split_free(pipe);
	//update last_command here i think
}

void	letsgo_pipe(char **pipe, char ***env, char **cash_question, char **last_command)
{
	char	**comm;
	pid_t	*pid;
	int		i;
	int		status;
//	int		fdr[4];		//maybe shared with pid[], redirections are opened before, cf "cat < file | tr a b >> file"

	pid = (pid_t *)ft_calloc(ft_split_len(pipe), sizeof(pid_t));
	status = 0;
	i = 0;
	while (pipe && pipe[i])
	{
		//redirection	//fdr[4]
		//cash_money
		if (!ft_strcmp(*last_command, "just to compile")) return ;
		//comm = ft_split_quotes(pipe[i], ' ');
		comm = ft_split(pipe[i], ' ');
		ft_split_trim_quotes(comm);
		if (comm && !pipe[1] && ft_isbuiltin(comm[0]) > 1)
			status = ft_exec_builtin(comm, env);
		else if (comm)
			ft_exec_pipe(comm, env, &pid[i]);	//fdr[4]
		ft_split_free(comm);
		i++;
	}
	letsgo_wait(ft_split_len(pipe), pid, status, cash_question);
}

void	letsgo_wait(int len, pid_t *pid, int status, char **cash_question)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (pid[i] > 0)
			waitpid(pid[i], &status, 0);
		i++;
	}
	free(*cash_question);
	*cash_question = ft_itoa(((status & 0xff00) >> 8));
	free(pid);
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
