/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_norm_norm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:05:37 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/04 18:05:50 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	trim_in_norm(t_mshl *r)
{
	r->str = r->triple[r->i][r->j];
	if (r->str[1] == 0)
		r->redir_heredoc = 0;
	else if (r->str[1] == '<' && r->str[2] == 0)
		r->redir_heredoc = 1;
	else
		return (3);
	ft_split_remove(r->triple[r->i], r->j);
	r->redir_in = ft_strdup(r->triple[r->i][r->j]);
	if (!r->redir_in)
		return (4);
	ft_split_remove(r->triple[r->i], r->j);
	r->redir_out_index -= 2;
	return (0);
}

int	trim_out_norm(t_mshl *r)
{
	r->str = r->triple[r->i][r->j];
	if (r->str[1] == 0)
		r->redir_app = 0;
	else if (r->str[1] == '>' && r->str[2] == 0)
		r->redir_app = 1;
	else
		return (6);
	ft_split_remove(r->triple[r->i], r->j);
	r->redir_out = ft_strdup(r->triple[r->i][r->j]);
	if (!r->redir_out)
		return (7);
	ft_split_remove(r->triple[r->i], r->j);
	return (0);
}

int	cash_get_var_line_too_long(t_mshl *k)
{
	int	asd;
	int	qwe;
	int	zxc;

	asd = (k->line[k->i] == '$');
	qwe = ft_env_namelen(&k->line[k->i + 1]);
	zxc = (k->quote != '\'');
	return (asd && qwe && zxc);
}

size_t	cash_money_line_too_long(t_mshl k)
{
	size_t	norminette_makes_me_a_better_programmer_thank_you;

	norminette_makes_me_a_better_programmer_thank_you = ft_strlcat
		(k.ret, k.var, ft_strlen(k.ret) + ft_strlen(k.var) + 1);
	return (norminette_makes_me_a_better_programmer_thank_you);
}

int	ft_export_magic_norm(t_mshl *b, int x)
{
	int	i_love_norm;
	int	norminette_is_fun;
	int	thank_god_for_norminette;

	i_love_norm = (!ft_strchr(b->comm[1], '='));
	norminette_is_fun = (ft_env_get(b->env_extra, b->comm[1]) != NULL);
	thank_god_for_norminette = (x == 0);
	return (i_love_norm && norminette_is_fun && thank_god_for_norminette);
}
