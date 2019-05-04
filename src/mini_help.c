/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 19:04:53 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/03 16:21:35 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_path(char *path)
{
	struct stat		stat;

	if (lstat(path, &stat) == -1)
		return (0);
	if (!(S_ISREG(stat.st_mode)) && !(S_ISLNK(stat.st_mode)))
		return (0);
	return (1);
}

void		mini_dsfree(char **str)
{
	int		i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		ft_strdel(&str[i]);
	free(str);
}

void	get_bin_path(char *bin, t_mini *mini)
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
