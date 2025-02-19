/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_fmt.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:22:54 by rdomange          #+#    #+#             */
/*   Updated: 2025/01/03 06:03:50 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_COLOR_FMT_H
# define FT_COLOR_FMT_H

// standard
# define CLR_BLK	"\033[30m"
# define CLR_RED	"\033[31m"
# define CLR_GRN	"\033[32m"
# define CLR_YEL	"\033[33m"
# define CLR_BLU	"\033[34m"
# define CLR_MAG	"\033[35m"
# define CLR_CYN	"\033[36m"
# define CLR_WHT	"\033[37m"
# define CLR_RST	"\033[0m"

// bright
# define CLR_BRIGHT_BLK	"\033[90m"
# define CLR_BRIGHT_RED	"\033[91m"
# define CLR_BRIGHT_GRN	"\033[92m"
# define CLR_BRIGHT_YEL	"\033[93m"
# define CLR_BRIGHT_BLU	"\033[94m"
# define CLR_BRIGHT_MAG	"\033[95m"
# define CLR_BRIGHT_CYN	"\033[96m"
# define CLR_BRIGHT_WHT	"\033[97m"

// background
# define BCLR_BLK	"\033[40m"
# define BCLR_RED	"\033[41m"
# define BCLR_GRN	"\033[42m"
# define BCLR_YEL	"\033[43m"
# define BCLR_BLU	"\033[44m"
# define BCLR_MAG	"\033[45m"
# define BCLR_CYN	"\033[46m"
# define BCLR_WHT	"\033[47m"

// bright background
# define BCLR_BRIGHT_BLK	"\033[100m"
# define BCLR_BRIGHT_RED	"\033[101m"
# define BCLR_BRIGHT_GRN	"\033[102m"
# define BCLR_BRIGHT_YEL	"\033[103m"
# define BCLR_BRIGHT_BLU	"\033[104m"
# define BCLR_BRIGHT_MAG	"\033[105m"
# define BCLR_BRIGHT_CYN	"\033[106m"
# define BCLR_BRIGHT_WHT	"\033[107m"

// text formatting
# define TXT_BOLD		"\033[1m"
# define TXT_DIM		"\033[2m"
# define TXT_UNDERLINE	"\033[4m"
# define TXT_BLINK		"\033[5m"
# define TXT_REVERSE	"\033[7m"
# define TXT_HIDDEN		"\033[8m"

#endif	//ft_color_fmt.h
