/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 08:42:42 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/10 08:21:29 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		mini_cdrepath(t_mini *mini)
{
	char		*path;
	char		*del;
	char		temp[PATH_MAX];

	del = ft_strjoin(mini_findpath(mini->ev, "PWD"), "/");
	path = ft_strjoin(del, mini->cmd[1]);
	ft_strdel(&del);
	if ((mini_chdir(path, mini->cmd[1])))
	{
		ft_strdel(&path);
		return ;
	}
	ft_strcpy(temp, mini_findpath(mini->ev, "PWD"));
	mini->ev = mini_pathva(mini->ev, "PWD", path);
	mini->ev = mini_pathva(mini->ev, "OLDPWD", temp);
	ft_strdel(&path);
}

static void		mini_cdback(t_mini *mini)
{
	char		path[PATH_MAX];
	char		temp[PATH_MAX];

	if (!(mini_findpath(mini->ev, "OLDPWD")))
	{
		ft_printf("cd : No OLDPWD Found\n");
		return ;
	}
	ft_strcpy(path, mini_findpath(mini->ev, "OLDPWD"));
	if ((mini_chdir(path, path)))
		return ;
	ft_strcpy(temp, mini_findpath(mini->ev, "PWD"));
	mini->ev = mini_pathva(mini->ev, "PWD", path);
	mini->ev = mini_pathva(mini->ev, "OLDPWD", temp);
}

static void		mini_cdhpath(t_mini *mini)
{
	char		*path;
	char		temp[PATH_MAX];

	path = ft_strjoin(mini_findpath(mini->ev, "HOME"), mini->cmd[1] + 1);
	if ((mini_chdir(path, path)))
	{
		ft_strdel(&path);
		return ;
	}
	ft_strcpy(temp, mini_findpath(mini->ev, "PWD"));
	mini->ev = mini_pathva(mini->ev, "PWD", path);
	mini->ev = mini_pathva(mini->ev, "OLDPWD", temp);
	ft_strdel(&path);
}

static void		mini_cdhome(t_mini *mini)
{
	char		path[PATH_MAX];
	char		temp[PATH_MAX];

	ft_strcpy(path, mini_findpath(mini->ev, "HOME"));
	if ((mini_chdir(path, path)))
		return ;
	ft_strcpy(temp, mini_findpath(mini->ev, "PWD"));
	mini->ev = mini_pathva(mini->ev, "PWD", path);
	mini->ev = mini_pathva(mini->ev, "OLDPWD", temp);
}

void			mini_cd(t_mini *mini)
{
	int		x;

	x = 0;
	while (mini->cmd[x])
		x++;
	if (x > 2)
	{
		dis_error(W_CDARG, NULL);
		return ;
	}
	if (!(mini_findpath(mini->ev, "HOME")) || !(mini_findpath(mini->ev, "PWD")))
		mini->ev = mini_fixenv(mini);
	if (!(mini->cmd[1]))
		mini_cdhome(mini);
	else if ((!(ft_strcmp(mini->cmd[1], "~")) && !(mini->cmd[2])))
		mini_cdhome(mini);
	else if ((ft_strcmp(mini->cmd[1], "~")) && (mini->cmd[1][0] == '~') &&
			!(mini->cmd[2]))
		mini_cdhpath(mini);
	else if (!(ft_strcmp(mini->cmd[1], "-")) && !(mini->cmd[2]))
		mini_cdback(mini);
	else if (mini->cmd[1] && !(mini->cmd[2]))
		mini_cdrepath(mini);
}
