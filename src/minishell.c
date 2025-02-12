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

void	ft_stress_test(char ****env, char **cash_question)
{
	int	i;
	int	fd;
	int	prev_fd;

	fd = open("stress_test.log", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	prev_fd = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	i = 0;
	while (i < 10000)
	{
		(*env)[0] = ft_export((*env)[0], "stress=ok");
		ft_printf("%s", ft_env_get((*env)[0], "stress"));
		ft_unset((*env)[0], "stress");
		ft_printf("unset");
		free(*cash_question);
		*cash_question = ft_itoa(0);
		ft_printf("%d\n", ft_atoi(*cash_question));
		i++;
	}
	dup2(prev_fd, STDOUT_FILENO);
	close(prev_fd);
	ft_printf("stress test ok\n");
}

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
	char	**comm;
	pid_t	*pid;	
	int		i;	//move deeper, 2 functions for pipe loop and wait loop
	int		s;	//minimum depth: needed in pipe loop, wait loop and cleanup

	add_history(input);
	//pipe = ft_split_quotes(input, '|');
	pipe = ft_split(input, '|');
	pid = (pid_t *)ft_calloc(ft_split_len(pipe), sizeof(pid_t));
	i = 0;
	while (pipe && pipe[i])
	{
		//redirection
		//cash_money
		//comm = ft_split_quotes(pipe[i], ' ');	//after, bigbrain
		comm = ft_split(pipe[i], ' ');
		ft_split_trim_quotes(comm);	//return -1 if unclosed
		if (comm && !pipe[1] && ft_isbuiltin(comm[0]) > 1)
			s = ft_exec_builtin(comm, env);
		else if (comm)
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
	free(*cash_question);
	*cash_question = ft_itoa(((s & 0xff00) >> 8));
	ft_split_free(pipe);
	free(pid);
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
//	(*env)[0] = ft_split("USER=user,PWD=/pwd,HOME=home,PATH=path", ',');
//	(*env)[0] = ft_export((*env)[0], "PATH");
//	ft_env_set((*env)[0], "PATH", ft_env_get(envp_main, "PATH"));
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
