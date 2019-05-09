/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 19:00:58 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/08 18:12:43 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		mini_process(t_mini *mini, char *full_path)
{
	pid_t		pid;

	pid = fork();
	if (pid == 0)
		execve(full_path, mini->cmd, mini->en);
	else
		wait(0);
}

static void		mini_fullpath(t_mini *mini)
{
	int				i;
	int				x;
	int				len;
	char			full_path[PATH_MAX];

	i = -1;
	while (mini->path[++i])
	{
		ft_strcpy(full_path, mini->path[i]);
		len = ft_strlen(mini->path[i]);
		full_path[len] = '/';
		x = -1;
		while (mini->cmd[0][++x])
			full_path[++len] = mini->cmd[0][x];
		full_path[++len] = '\0';
		if ((check_path(full_path)))
		{
			mini_process(mini, full_path);
			break ;
		}
	}
	if (mini->path[i] == NULL)
		dis_error(W_NOCMD, mini->cmd[0]);
}

int				mini_command(t_mini *mini)
{
	int		i;
	int		x;

	i = -1;
	x = 0;
	while (mini->Scmd[++i])
	{
		mini->cmd = ft_strsplit(mini->Scmd[i], ' ');
		if (!(mini->cmd[0]))
		{
			mini_dsfree(mini->cmd);
			return (0);
		}
		if (!(mini_check_build(mini, mini->cmd[0])))
			return (1);
		if (check_path(mini->cmd[0]))
			mini_process(mini, mini->cmd[0]);
		while (mini->cmd[++x])
		{
			if (mini->cmd[x][0] == '~')
				mini_full_path(mini);
		}
		get_bin_path("PATH", mini);
		mini_fullpath(mini);
		mini_dsfree(mini->path);
		mini_dsfree(mini->cmd);
	}
	return (0);
}
