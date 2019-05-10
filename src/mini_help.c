/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 19:04:53 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/10 08:15:18 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			mini_chdir(char *path, char *name)
{
	if (!(chdir(path)))
		return (0);
	else
	{
		if (access(path, F_OK) == -1)
			ft_printf("cd: no such file or directory: %s\n", name);
		else if (access(path, R_OK) == -1)
			ft_printf("cd: permission denied: %s\n", name);
		else
			ft_printf("cd: Not a directory: %s\n", name);
	}
	return (1);
}

void		mini_full_path(t_mini *mini)
{
	int		i;
	char	*temp;

	i = 0;
	while (mini->cmd[++i])
	{
		if (mini->cmd[i][0] == '~')
		{
			temp =\
				ft_strjoin(mini_findpath(mini->ev, "HOME"), mini->cmd[i] + 1);
			ft_strdel(&mini->cmd[i]);
			mini->cmd[i] = ft_strdup(temp);
			ft_strdel(&temp);
		}
	}
}

int			check_path(t_mini *mini, char *path)
{
	struct stat		stat;

	if (lstat(path, &stat) == -1)
		return (0);
	if (!(S_ISREG(stat.st_mode)) && !(S_ISLNK(stat.st_mode)))
		return (0);
	if ((S_ISREG(stat.st_mode)) && !(stat.st_mode & S_IXUSR) &&
			mini->cmd[1])
	{
		if (mini->cmd[1][0] == '~')
			return (mini_rerror(W_FIPER, path));
		else
			return (mini_rerror(W_FIPER, mini->cmd[1]));
	}
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

t_path		*mini_fix_help(int pa)
{
	t_path		*add;
	char		path[PATH_MAX];

	add = NULL;
	if (pa == E_HOME)
	{
		add = (t_path *)ft_memalloc(sizeof(t_path));
		add->pa = ft_strdup("HOME");
		add->va = ft_strdup(getpwuid(getuid())->pw_dir);
		add->next = NULL;
	}
	else if (pa == E_PWD)
	{
		getcwd(path, sizeof(path));
		add = (t_path *)ft_memalloc(sizeof(t_path));
		add->pa = ft_strdup("PWD");
		add->va = ft_strdup(path);
		add->next = NULL;
	}
	return (add);
}
