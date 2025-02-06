/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:13:08 by rdomange          #+#    #+#             */
/*   Updated: 2025/01/03 06:02:58 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BTREE_H
# define FT_BTREE_H

typedef struct s_btree
{
	void			*data;
	int				count;
	char			color;
	struct s_btree	*parent;
	struct s_btree	*left;
	struct s_btree	*right;
}	t_btree;

/*
bst_insert
rb_insert
heapq
*/

/*
skiena
search
insert
delete
print
successor/predecessor descendant
find_min

piscine
create_node
apply in, suff, pre fix
insert item
search item
level count
apply by level
*/

#endif	//ft_btree.h
