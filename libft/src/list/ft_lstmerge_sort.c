/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmerge_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:04:19 by rdomange          #+#    #+#             */
/*   Updated: 2025/01/07 17:04:20 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmerge_sort(t_list *l1, t_list *l2, int (cmp)(void *, void *))
{
	t_list	*ret;
	t_list	**tail;

	ret = NULL;
	tail = &ret;
	while (l1 && l2)
	{
		if (cmp(l1->data, l2->data) <= 0)
		{
			*tail = l1;
			l1 = l1->next;
		}
		else
		{
			*tail = l2;
			l2 = l2->next;
		}
		(*tail)->prev = NULL;
		tail = &((*tail)->next);
	}
	if (l1)
		*tail = l1;
	else
		*tail = l2;
	return (ret);
}
