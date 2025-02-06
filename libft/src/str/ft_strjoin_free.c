/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:58:51 by rdomange          #+#    #+#             */
/*   Updated: 2024/09/09 14:03:44 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int fr)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (s1 && (fr == 1 || fr == 3))
		ft_free (s1);
	if (s2 && (fr == 2 || fr == 3))
		ft_free (s2);
	return (ret);
}
