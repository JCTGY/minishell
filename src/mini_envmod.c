/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_envmod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:38:08 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/07 20:53:23 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_cmd_valid(t_mini *mini, int flag)
{
	if ((flag == 1 && (!(mini->cmd[1]) || mini->cmd[2])) ||
			(flag == 2 && (!(mini->cmd[1]) || !(mini->cmd[2]) || mini->cmd[3])))
	{
		(flag == 1) ? dis_error(W_UNSET) : 0;
		(flag == 2) ? dis_error(W_SETENV) : 0;
		return (1);
	}
	return (0);
}

static t_path	*remove_top(t_mini *mini)
{
	t_path		*top;

	top = mini->ev;
	ft_strdel(&(mini->ev->pa));
	ft_strdel(&(mini->ev->va));
	mini->ev = mini->ev->next;
	ft_memdel((void **)&top);
	return (mini->ev);
}

static t_path	*mini_set_add(t_mini *mini)
{
	t_path		*en;

	if (!(en = (t_path *)ft_memalloc(sizeof(t_path))))
		return (0);
	en->pa = ft_strdup(mini->cmd[1]);
	en->va = ft_strdup(mini->cmd[2]);
	en->next = NULL;
	return (en);
}

t_path			*mini_unsetenv(t_mini *mini)
{
	t_path		*temp;
	t_path		*del;
	t_path		*pre;

	if (check_cmd_valid(mini, 1))
		return (mini->ev);
	temp = mini->ev;
	if (!(ft_strcmp(mini->ev->pa, mini->cmd[1])))
		return (remove_top(mini));
	while (mini->ev)
	{
		if (!(ft_strcmp(mini->ev->pa, mini->cmd[1])))
		{
			del = mini->ev;
			ft_strdel(&(mini->ev->va));
			ft_strdel(&(mini->ev->pa));
			pre->next = mini->ev->next;
			ft_memdel((void **)&del);
			break ;
		}
		pre = mini->ev;
		mini->ev = mini->ev->next;
	}
	return (temp);
}

t_path			*mini_setenv(t_mini *mini)
{
	t_path		*temp;
	t_path		*pre;

	if (check_cmd_valid(mini, 2))
		return (mini->ev);
	temp = mini->ev;
	while (mini->ev)
	{
		if (!(ft_strcmp(mini->ev->pa, mini->cmd[1])))
		{
			ft_strdel(&(mini->ev->va));
			mini->ev->va = ft_strdup(mini->cmd[2]);
			break ;
		}
		pre = mini->ev;
		mini->ev = mini->ev->next;
	}
	if (pre->next == NULL)
		pre->next = mini_set_add(mini);
	return (temp);
}
