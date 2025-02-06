/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:58:25 by rdomange          #+#    #+#             */
/*   Updated: 2024/06/02 17:02:43 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *data)
{
	t_list	*ret;

	ret = (t_list *)ft_malloc(1 * sizeof(t_list));
	if (!ret)
		return (NULL);
	ret->data = data;
	ret->next = NULL;
	ret->prev = NULL;
	return (ret);
}
