/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 19:21:57 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/07 20:33:58 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		mini_dslist(t_mini *mini)
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

void		mini_dsfree(char **str)
{
	int			i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		ft_strdel(&str[i]);
	free(str);
}
