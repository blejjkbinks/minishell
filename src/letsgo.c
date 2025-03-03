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

void	letsgo_pipe(char **pipe, char ***env, char **cash_q, int *pidfd);
//char	**ready_pipe(char *input, char ***env, char **cash_q, char **last_c);
char	**ready_pipe(char *input, char **last_c);
void	*letsnot(char **cash_q, char **pipe, char **semicol, int *pidfd);
void	letsgo_wait(char **pipe, int *pidfd, char **cash_q, int status);

void	*letsgo(char *input, char ***env, char **cash_q, char **last_c)
{
	char	**semicol;
	char	**pipe;
	int		*pidfd;
	int		i;

	g_signal = 0;
	if (ft_isquoted_closed(input))
		return (letsnot(cash_q, NULL, NULL, NULL));
	semicol = ready_pipe(input, last_c);
	i = 0;
	while (semicol && semicol[i])
	{
		pipe = ft_split_quotes(semicol[i], '|');
		pidfd = (int *)ft_calloc(ft_split_len(pipe) * N, sizeof(int));
		if (redirection(pipe, pidfd) || invalid_pipe(input))
			return (letsnot(cash_q, pipe, semicol, pidfd));
		cash_money(pipe, env, *cash_q);
		ft_pidfd_debug(pipe, pidfd);
		ft_split_debug(pipe, "PIPE");
		letsgo_pipe(pipe, env, cash_q, pidfd);
		i++;
	}
	return (ft_split_free(semicol));
}

void	*letsnot(char **cash_q, char **pipe, char **semicol, int *pidfd)
{
	ft_free(*cash_q);
	if (pidfd && *pidfd == 258)
		*cash_q = ft_itoa(258);
	else if (g_signal == 2)
		*cash_q = ft_itoa(130);
	else
		*cash_q = ft_itoa(1);
	if (!pidfd && MS_CUTE)
		ft_printf("minishell: unclosed quote (┛ಠ益ಠ)┛彡┻━┻\n");
	if (!pidfd && !MS_CUTE)
		ft_printf("minishell: unclosed quote\n");
	redirection_close(pipe, pidfd);
	ft_free(pidfd);
	ft_split_free(pipe);
	ft_split_free(semicol);
	g_signal = 0;
	return (NULL);
}

//char	**ready_pipe(char *input, char ***env, char **cash_q, char **last_c)
char	**ready_pipe(char *input, char **last_c)
{
	char	**semicol;

	input = double_exclam(input, *last_c);
	ft_str_debug(*last_c, "LASTC_C");
	ft_str_debug(input, "D_EXC");
	add_history(input);
	ft_free(*last_c);
	*last_c = input;
	semicol = ft_split_quotes(input, ';');
	ft_split_debug(semicol, "SCOL");
	return (semicol);
}
//	input = cash_money(input, env, *cash_q);
//	ft_str_debug(input, "CASH");
//	ft_free(input);

void	letsgo_pipe(char **pipe, char ***env, char **cash_q, int *pidfd)
{
	char	**comm;
	int		i;
	int		status;

	status = 0;
	if (pipe && !pipe[1])
	{
		comm = ft_split_quotes(pipe[0], ' ');
		ft_splittrim_quotes(comm);
		if (comm && ft_isbuiltin(comm[0]) > 1)
			ft_split_debug(comm, "SINGLE");
		if (comm && ft_isbuiltin(comm[0]) > 1)
			status = (ft_exec_builtin(comm, env) << 8);
		else
			ft_exec_pipe(pipe, env, pidfd, 0);
		ft_split_free(comm);
	}
	i = 0;
	while (pipe && pipe[i] && pipe[1])
	{
		ft_exec_pipe(pipe, env, pidfd, i);
		i++;
	}
	letsgo_wait(pipe, pidfd, cash_q, status);
}
//ft_strtolower(comm[0]);

void	letsgo_wait(char **pipe, int *pidfd, char **cash_q, int status)
{
	int	i;

	ft_pidfd_debug(pipe, pidfd);
	swap_signal_for_execute();
	g_signal = 0;
	i = 0;
	while (pipe && pipe[i])
	{
		if (pidfd[N * i] > 0)
			waitpid(pidfd[N * i], &status, 0);
		i++;
	}
	swap_signal_for_execute();
	free(*cash_q);
	if (g_signal)
		*cash_q = ft_itoa(g_signal + 128);
	else
		*cash_q = ft_itoa(((status & 0xff00) >> 8));
	redirection_close(pipe, pidfd);
	free(pidfd);
	ft_split_free(pipe);
}
