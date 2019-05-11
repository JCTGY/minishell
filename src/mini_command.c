/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 19:00:58 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/10 16:43:15 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		mini_trpath(t_mini *mini)
{
	int		x;

	x = 0;
	while (mini->cmd[++x])
	{
		if (mini->cmd[x][0] == '~')
			mini_full_path(mini);
	}
}

static void		mini_process(t_mini *mini, char *full_path)
{
	pid_t		pid;

	if (mini->cmd[0][0] == '.' && mini->cmd[0][1] == '/')
	{
		if (access(&(mini->cmd[0][2]), X_OK))
		{
			mini_rerror(W_FIPER, mini->cmd[0]);
			mini->flag = 1;
			return ;
		}
		mini->flag = 1;
	}
	pid = fork();
	mini_nctrl();
	if (pid == 0)
		execve(full_path, mini->cmd, mini->en);
	else if (pid < 0)
	{
		ft_printf("Cannot Properly Fork\n");
		return ;
	}
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
		if ((check_path(mini, full_path)))
		{
			mini_process(mini, full_path);
			break ;
		}
	}
	if (mini->path[i] == NULL && !(mini->flag))
		dis_error(W_NOCMD, mini->cmd[0]);
	mini->flag = 0;
}

int				mini_command(t_mini *mini)
{
	while (mini->scmd[mini->i] != NULL)
	{
		mini->cmd = mini_split(mini->scmd[mini->i]);
		if (mini->cmd[0] && !(mini_check_build(mini->cmd[0])))
			mini_jump(mini);
		else if (mini->cmd[0] && check_path(mini, mini->cmd[0]))
			mini_process(mini, mini->cmd[0]);
		else if (mini->cmd[0])
		{
			mini_trpath(mini);
			if (get_bin_path("PATH", mini) != -1)
			{
				mini_fullpath(mini);
				mini_dsfree(mini->path);
			}
		}
		(mini->cmd) ? mini_dsfree(mini->cmd) : 0;
		mini->i += 1;
	}
	return (0);
}
