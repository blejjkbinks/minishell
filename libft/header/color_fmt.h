/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_fmt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:22:54 by rdomange          #+#    #+#             */
/*   Updated: 2024/09/19 18:29:06 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_FMT_H
# define COLOR_FMT_H

# ifndef FMT_RED
#  define FMT_RED	"\033[31m"
# endif
# ifndef FMT_GRN
#  define FMT_GRN	"\033[32m"
# endif
# ifndef FMT_YEL
#  define FMT_YEL	"\033[33m"
# endif
# ifndef FMT_BLU
#  define FMT_BLU	"\033[34m"
# endif
# ifndef FMT_MAG
#  define FMT_MAG	"\033[35m"
# endif
# ifndef FMT_CYN
#  define FMT_CYN	"\033[36m"
# endif
# ifndef FMT_WHT
#  define FMT_WHT	"\033[37m"
# endif
# ifndef FMT_BLK
#  define FMT_BLK	"\033[30m"
# endif
# ifndef FMT_RESET
#  define FMT_RESET	"\033[0m"
# endif

#endif	//color_fmt.h
