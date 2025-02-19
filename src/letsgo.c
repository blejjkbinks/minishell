/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letsgo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:45:03 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/18 14:45:04 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	letsgo(char *input, char ***env, char **cash_question, char **last_command);
void	letsgo_pipe(char **pipe, char ***env, char **cash_question, int *pidfd);
char	**ready_pipe(char *input, char ***env, char **cash_question, char **last_command);
//void	ready_comm()
void	letsgo_wait(char **pipe, int *pidfd, char **cash_question);


void	letsgo(char *input, char ***env, char **cash_question, char **last_command)
{
	char	**semicol;
	char	**pipe;
	int		*pidfd;
	int		i;

	if (ft_isquoted_closed(input))
	{
		if (MS_CUTE)
			ft_printf("minishell: unclosed quote (┛ಠ益ಠ)┛彡┻━┻\n");
		*cash_question = ft_itoa(1 + (long)ft_free(*cash_question));
		return ;
	}
	semicol = ready_pipe(input, env, cash_question, last_command);
	i = 0;
	while (semicol && semicol[i])
	{
		pipe = ft_split_quotes(semicol[i], '|');
		pidfd = (int *)ft_calloc(ft_split_len(pipe) * 3, sizeof(int));
		if (redirection(pipe, pidfd))
		{
			//update cash_question
			return ;
		}
		ft_pidfd_debug(pipe, pidfd);
		ft_split_debug(pipe, "PIPE");
		letsgo_pipe(pipe, env, cash_question, pidfd);
		i++;
	}
	ft_split_free(semicol);
}

char	**ready_pipe(char *input, char ***env, char **cash_question, char **last_command)
{
	char	**semicol;

	input = double_exclam(input, *last_command);
	add_history(input);
	ft_free(*last_command);
	*last_command = input;
	input = cash_money(input, env, *cash_question);
	semicol = ft_split_quotes(input, ';');
	ft_split_debug(semicol, "SCOL");
	ft_free(input);
	return (semicol);
}

void	letsgo_pipe(char **pipe, char ***env, char **cash_question, int *pidfd)
{
	char	**comm;
	int		i;

	i = 0;
	while (pipe && pipe[i])
	{
		comm = NULL;
		//status = (258 << 8);
		comm = ft_split_quotes(pipe[i], ' ');
		ft_splittrim_quotes(comm);
		ft_split_debug(comm, "COMM");
		//ft_strtolower(comm[0]);
		if (comm && !pipe[1] && ft_isbuiltin(comm[0]) > 1)
			pidfd[3 * i] = (ft_exec_builtin(comm, env) << 8);		//<< 8 is wrong, what of 0xff00 ??
		else if (comm)
			ft_exec_pipe(pipe, env, pidfd, i);
		ft_split_free(comm);
		i++;
	}
	letsgo_wait(pipe, pidfd, cash_question);
}

//void	ready_comm()

void	letsgo_wait(char **pipe, int *pidfd, char **cash_question)
{
	int	i;
	int	status;

	ft_pidfd_debug(pipe, pidfd);
	i = 0;
	while (pipe && pipe[i])
	{
		if (pidfd[3 * i] > 0)
			waitpid(pidfd[3 * i], &status, 0);
		i++;
	}
	free(*cash_question);
	*cash_question = ft_itoa(((status & 0xff00) >> 8));
	free(pidfd);
	ft_split_free(pipe);
}
