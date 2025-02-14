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

# ifndef MS_DEBUG
#  define MS_DEBUG 0
# endif

# ifndef MS_CUTE
#  define MS_CUTE 1
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
//main

//get_prompt.c
char	*get_prompt(char *prompt, char **env, int cash_question);

//find_builtin.c
int		ft_isbuiltin(char *str);
char	*ft_which(char *arg, char **env);

//exec_builtin.c
int		ft_exec_builtin(char **comm, char ***env);
//echo, exit, which_print

//probably source

//exec_pipe.c
void	ft_exec_pipe(char **comm, char ***env, pid_t *pid);
//exec_which

//redirection.c

//cash_money.c

//env_help.c
char	**ft_env_dup(char **env);
//char	*ft_env_name(char *name);
//int		ft_env_namelen(char *name);
int		ft_env_name(char *name, char **ret);
char	*ft_env_get(char **env, char *name);
int		ft_env_set(char **env, char *name, char *val);

//env_builtin.c
int		ft_env(char **env);
char	**ft_export(char **env, char *arg);
char	**ft_unset(char **env, char *name);
int		ft_export_magic(char *arg, char ***env, int x);
//room for magic_norm

//cd_pwd.c
char	*ft_getcwd(void);
int		ft_pwd(void);
int		ft_cd(char **arg, char **env);

#endif	//minishell.h