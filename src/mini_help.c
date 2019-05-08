/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 19:04:53 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/07 15:36:54 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_path		*mini_addlist(t_path *en, t_path *ev)
{
	t_path		*temp;

	if (!ev)
		return (en);
	temp = ev;
	while (ev->next)
		ev = ev->next;
	ev->next = en;
	return (temp);
}

t_path		*mini_addpath(char *envp)
{
	t_path		*en;
	char		**temp;

	if (!(en = (t_path *)ft_memalloc(sizeof(t_path))))
		return (NULL);
	temp = ft_strsplit(envp, '=');
	en->pa = ft_strdup(temp[0]);
	en->va = ft_strdup(temp[1]);
	en->next = NULL;
	mini_dsfree(temp);
	return (en);
}

int			check_path(char *path)
{
	struct stat		stat;

	if (lstat(path, &stat) == -1)
		return (0);
	if (!(S_ISREG(stat.st_mode)) && !(S_ISLNK(stat.st_mode)))
		return (0);
	return (1);
}

void		get_bin_path(char *bin, t_mini *mini)
{
	int		i;
	char	*path;

	i = -1;
	while (mini->en[++i])
	{
		if (ft_strstr(mini->en[i], bin))
			path = ft_strdup(ft_strchr(mini->en[i], '/'));
	}
	mini->path = ft_strsplit(path, ':');
	ft_strdel(&path);
}
