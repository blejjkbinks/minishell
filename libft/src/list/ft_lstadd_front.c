/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:04:44 by rdomange          #+#    #+#             */
/*   Updated: 2024/06/03 19:29:29 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *add)
{
	if (!add)
		return ;
	if (!lst)
	{
		lst = &add;
		return ;
	}
	if (*lst)
	{
		add->next = *lst;
		(*lst)->prev = add;
	}
	*lst = add;
}
