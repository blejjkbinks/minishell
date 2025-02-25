/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:21:28 by rdomange          #+#    #+#             */
/*   Updated: 2025/02/08 10:21:29 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_prompt_delim(char *d[9]);
static char	*ft_join_prompt(char *e[9]);
static char	*ft_get_git_branch(void);

char	*get_prompt(char *p, char **env, int cash_question)
{
	char	*pwd;
	char	*branch;
	char	*e[9];

	ft_free(p);
	if (!MS_CUTE)
		return (ft_strdup("minishell$ "));
	pwd = ft_env_get(env, "PWD");
	e[1] = ft_env_get(env, "USER");
	if (ft_strchr(pwd, '/') == ft_strrchr(pwd, '/'))
		e[3] = pwd + 1;
	else if (!ft_strcmp(pwd, ft_env_get(env, "HOME")))
		e[3] = "~";
	else
		e[3] = ft_strrchr(pwd, '/') + 1;
	branch = ft_get_git_branch();
	e[5] = ft_strrchr(branch, '/');
	if (cash_question == 0)
		e[7] = CLR_GRN ":3";
	else
		e[7] = CLR_RED ":(";
	ft_prompt_delim(e);
	p = ft_join_prompt(e);
	free(branch);
	return (p);
}

static void	ft_prompt_delim(char *d[9])
{
	d[0] = CLR_BRIGHT_BLK "$minishell$ " CLR_CYN;
	d[2] = CLR_BRIGHT_BLK "@" CLR_BLU " ./" CLR_BRIGHT_BLU;
	d[4] = " ";
	d[6] = "";
	d[8] = CLR_RST " $ ";
	if (d[5])
	{
		d[4] = CLR_MAG " (";
		d[5]++;
		d[6] = ") " CLR_RST;
	}
}

static char	*ft_join_prompt(char *e[9])
{
	int		len;
	int		i;
	char	*ret;

	len = 0;
	i = 0;
	while (i < 9)
	{
		len += ft_strlen(e[i]);
		i++;
	}
	ret = (char *)ft_malloc((len + 1) * sizeof(char));
	ret[0] = 0;
	i = 0;
	while (i < 9)
	{
		ft_strlcat(ret, e[i], len + 1);
		i++;
	}
	return (ret);
}

static char	*ft_get_git_branch(void)
{
	char	*branch;
	char	*pwd;
	int		fd;

	pwd = ft_getcwd();
	while (ft_strchr(pwd, '/'))
	{
		branch = ft_strjoin(pwd, "/.git/HEAD");
		fd = open(branch, O_RDONLY);
		free(branch);
		if (fd > 0)
			break ;
		*ft_strrchr(pwd, '/') = 0;
	}
	free(pwd);
	if (fd < 0)
		return (NULL);
	branch = get_next_line(fd);
	close(fd);
	return (branch);
}
