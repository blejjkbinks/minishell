/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:06:19 by rdomange          #+#    #+#             */
/*   Updated: 2024/06/02 17:41:51 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *add)
{
	t_list	*last;

	if (!add)
		return ;
	if (*lst)
	{
		last = ft_lstlast(*lst);
		last->next = add;
		add->prev = last;
	}
	else
		*lst = add;
}
