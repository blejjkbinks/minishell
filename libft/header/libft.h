/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:29:39 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/07 16:19:36 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>		//malloc and free
# include <unistd.h>		//write and read
# include <fcntl.h>			//open and close
# include <stddef.h>		//size_t
# include <limits.h>		//INT_MAX
# include <stdarg.h>		//va_arg
# include <errno.h>
# include "ft_color_fmt.h"
# include "ft_bool.h"
# include "ft_list.h"
# include "ft_btree.h"
//# include <stdio.h>		//debug, remove when done

# ifndef DEFAULT_CAP
#  define DEFAULT_CAP 16
# endif

//mem
void	*ft_memset(void *s, int c, size_t len);
void	ft_bzero(void *s, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t len);
int		ft_memcmp(const void *s1, const void *s2, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	*ft_realloc(void *ptr, size_t old, size_t new_cap, size_t *cap);
char	*ft_strdup(const char *str);

//str
size_t	ft_strlen(const char *str);
size_t	ft_strnlen(const char *str, size_t maxlen);
size_t	ft_strlcpy(char *dst, const char *src, size_t maxlen);
size_t	ft_strlcat(char *dst, const char *src, size_t maxlen);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strnstr(const char *str, const char *find, size_t len);
char	*ft_substr(const char *str, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strjoin_free(char *s1, char *s2, int fr);
char	*ft_strnjoin(int count, ...);
char	*ft_strtrim(const char *str, const char *set);
int		ft_strtrim_quotes(char *str);

//split
char	**ft_split(const char *str, char d);
char	**ft_split_set(const char *str, const char *d);
char	**ft_split_free(char **split);
char	**ft_split_realloc(char **split, size_t new_cap, size_t *cap_ptr);
int		ft_split_len(char **split);
char	**ft_split_remove(char **split, int r);
int		ft_isquoted(char c, int *q);
char	**ft_split_quotes(const char *str, char d);
void	ft_split_trim_quotes(char **split);

//chr
int		ft_isspace(int c);
int		ft_isalpha_lower(int c);
int		ft_isalpha_upper(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_strisdigit(char *str);
char	*ft_strtoupper(char *str);
char	*ft_strtolower(char *str);
char	*ft_strcapital(char *str);

//nbr
long	ft_atoi(const char *str);
char	*ft_itoa(long nbr);
char	*ft_atoabase(char *str, int src_b, int dst_b);
char	*ft_itoa_ulong(unsigned long nbr);
int		ft_nbrlen(long nbr);
int		ft_min(int a, int b);
int		ft_max(int a, int b);
int		ft_abs(int x);
int		ft_numcmp(int a, int b);

//wrt
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putnbr(long nbr);
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *str, int fd);
int		ft_putendl_fd(char *str, int fd);
int		ft_putnbr_fd(long nbr, int fd);
char	*get_next_line(int fd);
int		ft_printf(const char *fmt, ...);

//fun
void	ft_test_libft(void);
void	*ft_free(void *ptr);
void	*ft_malloc(size_t size);
void	*ft_printmemory(void *ptr, size_t len);
int		ft_bit(void *ptr, int i, int val);
void	ft_sort(int *arr, int n);

#endif	//libft.h
