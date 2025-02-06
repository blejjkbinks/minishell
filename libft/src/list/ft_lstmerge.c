/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:09:47 by rdomange          #+#    #+#             */
/*   Updated: 2025/01/07 16:09:48 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmerge(t_list *lst1, t_list *lst2)
{
	t_list	*tmp;

	if (!lst1)
		return (lst2);
	if (!lst2)
		return (lst1);
	tmp = ft_lstlast(lst1);
	tmp->next = lst2;
	lst2->prev = tmp;
	return (lst1);
}
