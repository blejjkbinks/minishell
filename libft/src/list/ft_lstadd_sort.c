/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:04:34 by rdomange          #+#    #+#             */
/*   Updated: 2025/01/07 17:04:36 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_sort(t_list **lst, t_list *add, int (*cmp)(void *, void *))
{
	t_list	*cur;

	if (!lst || !add)
		return ;
	if (!*lst || cmp(add->data, (*lst)->data) <= 0)
	{
		ft_lstadd_front(lst, add);
		return ;
	}
	cur = *lst;
	while (cur->next && cmp(add->data, cur->next->data) > 0)
		cur = cur->next;
	add->next = cur->next;
	add->prev = cur;
	if (cur->next)
		cur->next->prev = add;
	cur->next = add;
}
