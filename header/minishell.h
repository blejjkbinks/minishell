/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:37:46 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/06 14:37:49 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef MS_HEREDOC_PATH
#  define MS_HEREDOC_PATH "/tmp/minishell_heredoc.txt"
# endif

# ifndef N
#  define N 4
# endif

# include "../libft/header/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>

//minishell.c
//main, init

//debug.c
void	ft_split_debug(char **split, char *msg);
void	ft_pidfd_debug(char **split, int *pidfd);
void	ft_str_debug(char *str, char *msg);
void	ft_dup_debug(int a, int b, char *msg);

//get_prompt.c
char	*get_prompt(char *prompt, char **env, int cash_question);

//letsgo.c
void	*letsgo(char *input, char ***env, char **cash_q, char **last_c);
//letsgo_pipe, ready_pipe, ready_comm, letsgo_wait

//find_builtin.c
int		ft_isbuiltin(char *str);
char	*ft_which(char *arg, char **env);

//exec_builtin.c
int		ft_exec_builtin(char **comm, char ***env);
int		ft_source(char *arg, char ***env);
//echo, exit, which_print

//exec_pipe.c
void	ft_exec_pipe(char **comm, char ***env, int *pidfd, int i);
//exec_which

//redirection.c
int		redirection(char **pipe, int *pidfd);
void	redirection_close(char **pipe, int *pidfd);

//redir_help.c
int		find_redirection(char *str, int *rin, int *rout);
int		find_mode(char *str, int *i, int *mode);
int		trim_redirection(char *str, int mode, int *rin, int *rout);
int		open_redirection(char *str, int mode, int *rin, int *rout);
int		open_heredoc(char *str);

//cash_money.c
char	*cash_money(char *str, char ***env, char *cash_q);

//double_exclam.c
char	*double_exclam(char *str, char *last_c);

//env_help.c
char	**ft_env_dup(char **env);
int		ft_env_name(char *name, char **ret);
char	*ft_env_get(char **env, char *name);
int		ft_env_set(char **env, char *name, char *val);

//env_builtin.c
int		ft_env(char **env);
char	**ft_export(char **env, char *arg);
char	**ft_unset(char **env, char *name);
int		ft_export_magic(char *arg, char ***env, int x, int len);

//cd_pwd.c
char	*ft_getcwd(void);
int		ft_pwd(void);
int		ft_cd(char **arg, char **env);

#endif	//minishell.h