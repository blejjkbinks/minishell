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
# include <signal.h>

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
	char	*var;
	char	*ret;
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

//env.c
char	**ft_env_dup(char **env);
char	*ft_env_name(char *name);
int		ft_env_namelen(char *name);
char	*ft_env_get(char **env, char *name);
int		ft_env_set(char **env, char *name, char *val);

//env_norm.c
char	**ft_export(char **env, char *arg);
int		ft_unset_norm(char **env, int j);
char	**ft_unset(char **env, char *name);
int		ft_env(char **env);

//cd_pwd.c
char	*ft_getcwd(void);
int		ft_pwd(void);
int		ft_cd(char **arg, char **env);

//builtin.c
int		is_builtin(char *str);
int		is_builtin_dontfork(char *str);
char	*ft_which(char *arg, char **env);
int		ft_echo(char **arg);

//variable_expand.c
int		quoted(char c, char *quote);
int		tilda(char *str, int len, char quote);
int		double_exclam(char *str, int i);
char	*cash_money(t_mshl k);

//split_quotes.c
void	finaly_done_with_norm(t_mshl *o);
char	**ft_split_quotes(char *str, char d);
char	***ft_split_triple(char *line);
void	ft_free_triple(char ***triple);

//norm_norm_norm.c
int		trim_in_norm(t_mshl *r);
int		trim_out_norm(t_mshl *r);
size_t	cash_money_line_too_long(t_mshl k);
int		cash_get_var_line_too_long(t_mshl *k);
int		ft_export_magic_norm(t_mshl *b, int x);

//redirection.c
int		trim_redirection_in(t_mshl *r);
int		trim_redirection_out(t_mshl *r);
int		index_redirection(char *line, t_mshl *r);
int		get_redir_info(t_mshl *m);

//open_redirections.c
int		ft_open_redirs(t_mshl *m);
int		ft_open_redirs_in(t_mshl *m);
int		ft_open_redirs_in_norm(t_mshl *m);

//letsgo_norm.c
void	letsgo_getready(t_mshl *m);
void	letsgo_cleanup(t_mshl *m);
void	ft_ready_pipe(t_mshl *m);
void	ft_cleanup_pipe(t_mshl *m);

//exec_norm.c
int		ft_exec_builtin(t_mshl *b);
int		ft_export_magic(t_mshl *b, int x);
int		ft_which_print(char **arg, char **env);

//exec.c
int		ft_exec_which(char **arg, char **env);
int		ft_exec_bash_script(char **arg, char **env);
void	ft_exec_pipe_segment_norm(t_mshl *m);
void	ft_exec_pipesegment(t_mshl *m);

//signal.c
void	init_signals(void);
void	ms_sig_interupt(int signo);
void	ms_sig_interupt_alt(int signo);
void	swap_signal_for_execute(void);

#endif	//minishell.h
