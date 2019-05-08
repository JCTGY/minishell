/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 19:00:58 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/07 19:31:58 by jchiang-         ###   ########.fr       */
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
		if (!mini->cmd[0] || !(mini->cmd))
			return ;
		ft_strcpy(full_path, mini->path[i]);
		len = ft_strlen(mini->path[i]);
		full_path[len] = '/';
		x = -1;
		while (mini->cmd[0][++x])
			full_path[++len] = mini->cmd[0][x];
		full_path[++len] = '\0';
		if ((check_path(full_path)))
			mini_process(mini, full_path);
	}
}

int				mini_command(t_mini *mini)
{
	int		i;

	i = -1;
	while (mini->Scmd[++i])
	{
		mini->cmd = ft_strsplit(mini->Scmd[i], ' ');
		if (!(mini->cmd[0]))
			return (0);
		if (!(mini_check_build(mini, mini->cmd[0])))
			return (1);
		get_bin_path("PATH", mini);
		mini_fullpath(mini);
		mini_dsfree(mini->path);
		mini_dsfree(mini->cmd);
	}
	return (0);
}
