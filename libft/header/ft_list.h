/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:01:43 by rdomange          #+#    #+#             */
/*   Updated: 2025/01/03 06:01:20 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

t_list	*ft_lstcreate_node(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstfind(t_list *lst, void *data);
t_list	*ft_lstindex_at(t_list *lst, int index);
int		ft_lstindex_get(t_list *lst, t_list *find);
int		ft_lstlen(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *add);
void	ft_lstadd_back(t_list **lst, t_list *add);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));

void	ft_lstsort(t_list **lst, int (*cmp)(void *, void *));
void	ft_lstreverse(t_list **lst);
t_list	*ft_lstmerge(t_list *lst1, t_list *lst2);
t_list	*ft_lstmerge_sort(t_list *l1, t_list *l2, int (cmp)(void *, void *));
void	ft_lstadd_sort(t_list **lst, t_list *add, int (*cmp)(void *, void *));
void	ft_lstremove(t_list **lst, t_list *rem, void (*del)(void *));
void	ft_lstprint(t_list *lst, char t);

#endif	//ft_list.h
