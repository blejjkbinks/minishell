/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:34:28 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/20 13:34:29 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_sig_handler(int signo)
{
	g_signal = signo;
	write(1, "\n", 1);
}

static void	set_heredoc_signal_handler(struct sigaction *old_action)
{
	struct sigaction	int_new_action;

	int_new_action.sa_handler = heredoc_sig_handler;
	sigemptyset(&int_new_action.sa_mask);
	int_new_action.sa_flags = 0;
	sigaction(SIGINT, &int_new_action, old_action);
}

void	reading_input(int *interrupted, int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		ft_printf("'%s'> ", delimiter);
		line = get_next_line(0);
		if (g_signal == 2)
		{
			*interrupted = 1;
			return ;
		}
		if (!line && g_signal == 0)
		{
			ft_printf("\n");
			return ;
		}
		ft_printf("heredoc_debug: '%s'\n", line);
		if (!ft_strncmp(line, delimiter, ft_strlen(line) - 1) && line)
		{
			ft_printf("heredoc_debug: !ft_strncmp\n");
			free(line);
			return ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

int	open_heredoc(char *delimiter)
{
	struct sigaction	old_action;
	int					fd;
	int					interrupted;

	interrupted = 0;
	fd = open(MS_HEREDOC_PATH, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	set_heredoc_signal_handler(&old_action);
	reading_input(&interrupted, fd, delimiter);
	close(fd);
	sigaction(SIGINT, &old_action, NULL);
	if (interrupted)
		return (-5);
	return (open(MS_HEREDOC_PATH, O_RDONLY));
}
