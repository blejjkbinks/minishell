/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:01:00 by rdomange          #+#    #+#             */
/*   Updated: 2025/01/07 17:01:01 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsort(t_list **lst, int (*cmp)(void *, void *))
{
	t_list	*cur;
	void	*tmp;
	int		swp;

	if (!lst || !*lst)
		return ;
	swp = 1;
	while (swp)
	{
		swp = 0;
		cur = *lst;
		while (cur && cur->next)
		{
			if (cmp(cur->data, cur->next->data) > 0)
			{
				tmp = cur->data;
				cur->data = cur->next->data;
				cur->next->data = tmp;
				swp = 1;
			}
			cur = cur->next;
		}
	}
}
