/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 08:30:39 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/10 17:16:37 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			init_envp(t_mini *mini, char **envp)
{
	int		i;

	i = -1;
	mini->ev = NULL;
	while (envp[++i])
		mini->ev = mini_addlist(mini_addpath(envp[i]), mini->ev);
}

static void			get_arg(char **msg)
{
	int		ret;
	char	buff[2];
	char	*temp;

	*msg = ft_strnew(0);
	ret = 0;
	while ((ret = read(0, &buff, 1) && buff[0] != '\n'))
	{
		temp = *msg;
		buff[1] = '\0';
		*msg = ft_strjoin(temp, buff);
		free(temp);
	}
}

static void			display_header(void)
{
	int		fd;
	char	buff[2];

	if ((fd = open("mini_head", O_RDONLY)) < 0)
		return ;
	while (read(fd, buff, 1) > 0)
	{
		buff[1] = '\0';
		write(1, "\e[1;95m", 8);
		write(1, &buff[0], 1);
		write(1, "\e[0m", 4);
	}
	close(fd);
}

int					main(int argc, char **argv, char **envp)
{
	char		*str;
	t_mini		mini;

	(void)argc;
	(void)argv;
	ft_bzero(&mini, sizeof(mini));
	display_header();
	init_envp(&mini, envp);
	mini_refenv(&mini, mini.ev);
	while (42)
	{
		mini_ctrl();
		write(1, "\e[1;95m87SHELL> \e[0m", 20);
		get_arg(&str);
		mini.scmd = ft_strsplit(str, ';');
		mini.i = 0;
		mini_command(&mini);
		ft_strdel(&str);
		mini_dsfree(mini.scmd);
	}
	return (0);
}
