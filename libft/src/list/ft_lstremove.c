/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:00:01 by rdomange          #+#    #+#             */
/*   Updated: 2025/01/07 16:00:05 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstremove(t_list **lst, t_list *rem, void (*del)(void *))
{
	if (!lst || !*lst || !rem)
		return ;
	if (rem->prev)
		rem->prev->next = rem->next;
	if (rem->next)
		rem->next->prev = rem->prev;
	if (*lst == rem)
		*lst = rem->next;
	ft_lstdelone(rem, del);
}
