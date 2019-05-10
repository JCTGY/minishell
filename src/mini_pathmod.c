/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pathmod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 09:10:30 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/09 09:09:54 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*mini_findpath(t_path *mini, char *str)
{
	t_path		*en;

	en = mini;
	while (en)
	{
		if (!(ft_strcmp(en->pa, str)))
			return (en->va);
		en = en->next;
	}
	return (NULL);
}

t_path		*mini_pathva(t_path *en, char *pa, char *va)
{
	t_path		*temp;

	temp = en;
	while (en)
	{
		if (!(ft_strcmp(en->pa, pa)))
		{
			ft_strdel(&en->va);
			en->va = ft_strdup(va);
		}
		en = en->next;
	}
	return (temp);
}

t_path		*mini_addlist(t_path *en, t_path *ev)
{
	t_path		*temp;

	if (!ev)
		return (en);
	temp = ev;
	while (ev->next)
		ev = ev->next;
	ev->next = en;
	return (temp);
}

t_path		*mini_addpath(char *envp)
{
	t_path		*en;
	char		**temp;

	if (!(en = (t_path *)ft_memalloc(sizeof(t_path))))
		return (NULL);
	temp = ft_strsplit(envp, '=');
	en->pa = ft_strdup(temp[0]);
	en->va = ft_strdup(temp[1]);
	en->next = NULL;
	mini_dsfree(temp);
	return (en);
}

t_path		*mini_fixenv(t_mini *mini)
{
	t_path		*temp;
	t_path		*add;

	temp = mini->ev;
	add = mini->ev;
	while (add->next)
		add = add->next;
	if (!(mini_findpath(mini->ev, "HOME")))
	{
		add->next = mini_fix_help(E_HOME);
		add = add->next;
	}
	if (!(mini_findpath(mini->ev, "PWD")))
	{
		add->next = mini_fix_help(E_PWD);
		add = add->next;
	}
	return (temp);
}
