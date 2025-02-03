/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:58:57 by rdomange          #+#    #+#             */
/*   Updated: 2024/09/19 20:00:37 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/header/libft.h"
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

typedef struct s_mshl
{
	char	*line;
	char	*cash;
	char	*prompt;
	char	*name;
	char	*last_command;
	char	*str;
	char	*str1;
	char	*str2;
	char	*str3;
	char	*exit_status;
	int		exit_res;
	char	**env;
	char	**env_extra;
	char	**pipe;
	char	**comm;
	char	***triple;
	char	c;
	char	d;
	int		i;
	int		j;
	int		k;
	int		len;
	size_t	cap;
	size_t	cap2;
	pid_t	pid;
	char	quote;
	int		redir_app;
	int		redir_heredoc;
	char	*redir_in;
	char	*redir_out;
	char	*tmp_heredoc;
	char	*line2;
	int		fd_in;
	int		fd_out;
	int		flags;
	int		pipefd[2];
	int		prevfd;
	int		redir_in_index;
	int		redir_out_index;
	int		is_first;
	int		is_last;
	pid_t	pids[99];
	int		waitpid_status;
}	t_mshl;

char	**ft_env_dup(char **env);
char	*ft_env_name(char *name);
int		ft_env_namelen(char *name);
char	*ft_env_get(char **env, char *name);
int		ft_env_set(char **env, char *name, char *val);

char	**ft_export(char **env, char *arg);
char	**ft_unset(char **env, char *name);
int		ft_env(char **env);

char	*ft_getcwd(void);
int		ft_pwd(void);
int		ft_cd(char **arg, char **env);

int		is_builtin(char *str);
int		is_builtin_dontfork(char *str);
char	*ft_which(char *arg, char **env);
int		ft_echo(char **arg);

int		quoted(char c, char *quote);
char	*cash_money(t_mshl k);

char	**ft_split_quotes(char *str, char d);
char	***ft_split_triple(char *line);
void	ft_free_triple(char ***triple);

int		index_redirection(char *line, t_mshl *r);
int		trim_redirection(t_mshl *r);
int		get_redir_info(t_mshl *m);

int		ft_exec_builtin(t_mshl *b);
int		ft_exec_which(int *status, char **arg, char **env);
int		ft_exec_single(t_mshl *m, char **arg, char **env);
int		ft_exec_pipesegment(t_mshl *m);

#endif	//minishell.h
