/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 22:54:30 by rdomange          #+#    #+#             */
/*   Updated: 2024/09/08 22:54:33 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old, size_t new, size_t *cap)
{
	void	*ret;

	if (!ptr || new < old)
		return (ptr);
	ret = (void *)ft_calloc(new, sizeof(char));
	if (!ret)
		return (ptr);
	ft_memcpy(ret, ptr, old);
	ft_free (ptr);
	if (cap)
		*cap = new;
	return (ret);
}
