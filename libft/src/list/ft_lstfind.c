/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 21:02:29 by rdomange          #+#    #+#             */
/*   Updated: 2024/06/23 21:07:03 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *lst, void *data)
{
	t_list	*node;

	node = lst;
	while (node)
	{
		if (*(int *)node->data == *(int *)data)
			return (node);
		node = node->next;
	}
	return (NULL);
}
