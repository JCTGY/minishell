/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 08:30:39 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/03 21:17:59 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			init_envp(t_mini *mini, char **envp)
{
	int		len;
	int		i;

	len = 0;
	while (envp[len])
		len++;
	i = -1;
	if (!(mini->en = (char **)ft_memalloc(sizeof(char *) * len)))
		return ;
	while (envp[++i])
		mini->en[i] = ft_strdup(envp[i]);
	mini->en[i] = 0;
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

	if ((fd = open("headder", O_RDONLY)) < 0)
		return ;
	while (read(fd, buff, 1) > 0)
	{
		buff[1] = '\0';
		ft_putchar(buff[0]);
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
	while (42)
	{
		ft_printf("mini> ");
		get_arg(&str);
		mini.Scmd = ft_strsplit(str, ';');
		if (mini_command(&mini) == -1)
			break ;
		ft_strdel(&str);
		mini_dsfree(mini.Scmd);
	}
	return (0);
}
