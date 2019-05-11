/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 19:21:57 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/10 17:35:32 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		mini_lislen(t_path *dup)
{
	int			len;

	len = 0;
	while (dup)
	{
		dup = dup->next;
		len++;
	}
	return (len);
}

void			mini_refenv(t_mini *mini, t_path *ev)
{
	t_path		*cp;
	char		*temp;
	char		*del;
	int			x;
	int			len;

	cp = ev;
	if (mini->en)
		mini_dsfree(mini->en);
	len = mini_lislen(cp);
	if (!(mini->en = (char **)ft_memalloc(sizeof(char *) * len)))
		return ;
	x = 0;
	while (cp)
	{
		temp = ft_strjoin(cp->pa, "=");
		del = ft_strjoin(temp, cp->va);
		mini->en[x] = ft_strdup(del);
		ft_strdel(&temp);
		ft_strdel(&del);
		cp = cp->next;
		x++;
	}
	mini->en[x] = NULL;
}

void			mini_dslist(t_mini *mini)
{
	t_path		*temp;

	while (mini->ev)
	{
		temp = mini->ev;
		ft_strdel(&(mini->ev->pa));
		ft_strdel(&(mini->ev->va));
		mini->ev = mini->ev->next;
		free(temp);
	}
}

void			mini_dsfree(char **str)
{
	int		x;
	int		i;

	x = 0;
	i = 0;
	if (!str)
		return ;
	while (str[x])
		x++;
	while (i < x)
	{
		ft_strdel(&(str[i]));
		i++;
	}
	free(str);
}
