/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:57:13 by rdomange          #+#    #+#             */
/*   Updated: 2024/06/23 21:06:08 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstindex(t_list *lst, t_list *find)
{
	int		i;
	t_list	*node;

	i = 0;
	node = lst;
	while (node)
	{
		if (node == find)
			return (i);
		node = node->next;
		i++;
	}
	return (-1);
}
