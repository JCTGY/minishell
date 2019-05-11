/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_jump.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:54:18 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/10 15:46:13 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			mini_print_env(t_mini *mini)
{
	t_path		*en;

	en = mini->ev;
	while (en)
	{
		ft_printf("%s=%s\n", en->pa, en->va);
		en = en->next;
	}
	return (1);
}

int					mini_jump(t_mini *mini)
{
	if (!(ft_strcmp(mini->cmd[0], "env")))
		mini_print_env(mini);
	else if (!(ft_strcmp(mini->cmd[0], "setenv")))
		mini->ev = mini_setenv(mini);
	else if (!(ft_strcmp(mini->cmd[0], "unsetenv")))
		mini->ev = mini_unsetenv(mini);
	else if (!(ft_strcmp(mini->cmd[0], "cd")))
		mini_cd(mini);
	else if (!(ft_strcmp(mini->cmd[0], "echo")))
		mini_echo(mini);
	else if (!(ft_strcmp(mini->cmd[0], "exit")))
	{
		mini_dslist(mini);
		mini_dsfree(mini->cmd);
		exit(0);
	}
	return (1);
}

int					mini_check_build(char *str)
{
	if (!(ft_strcmp(str, "env")) || !(ft_strcmp(str, "setenv")) ||
			!(ft_strcmp(str, "unsetenv")) || !(ft_strcmp(str, "exit")) ||
			!(ft_strcmp(str, "cd")) || !(ft_strcmp(str, "echo")))
		return (0);
	return (1);
}
