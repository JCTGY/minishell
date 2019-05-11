/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 08:33:40 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/10 17:43:15 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		mini_quot(char c)
{
	return ((c == '\'') || (c == '\"'));
}

int				mini_prquot(t_mini *mini, char *q, int i)
{
	char		c;

	c = q[i++];
	while (q[i] && q[i] != c)
	{
		if (q[i] == '$')
			i = mini_dapr(mini, q, i);
		ft_putchar(q[i++]);
	}
	return (i);
}

int				mini_dapr(t_mini *mini, char *q, int i)
{
	char	name[NAME_MAX];
	int		x;

	x = 0;
	while (q[i++])
	{
		if (mini_quot(q[i]))
		{
			ft_putchar('$');
			i = mini_prquot(mini, q, i);
		}
		else if (ft_isspace(q[i]) || q[i] == '$')
			break ;
		else
			name[x++] = q[i];
	}
	name[x] = '\0';
	if (x && mini_findpath(mini->ev, name))
		ft_printf("%s", mini_findpath(mini->ev, name));
	i--;
	return (i);
}

static int		mini_checkquot(char *str)
{
	int		tab[2];

	tab[0] = 0;
	tab[1] = 0;
	while (*str)
	{
		if (!tab[0] && *str == '\'')
			tab[0]++;
		else if (tab[0] && *str == '\'')
			tab[0]--;
		if (!tab[1] && *str == '\"')
			tab[1]++;
		else if (tab[1] && *str == '\"')
			tab[1]--;
		str++;
	}
	if (!tab[0] || !tab[1])
		return (0);
	return (1);
}

int				mini_echo(t_mini *mini)
{
	int		i;

	i = 5;
	if (mini_checkquot(mini->scmd[mini->i]))
		return (mini_rerror(W_ECARG, NULL));
	while (mini->scmd[mini->i][i])
	{
		if (mini_quot(mini->scmd[mini->i][i]))
			i = mini_prquot(mini, mini->scmd[mini->i], i);
		else if (mini->scmd[mini->i][i] == '$')
			i = mini_dapr(mini, mini->scmd[mini->i], i);
		else if (ft_isspace(mini->scmd[mini->i][i]) &&
				!(ft_isspace(mini->scmd[mini->i][i - 1])))
		{
			ft_putchar(' ');
			i++;
		}
		else if (ft_isspace(mini->scmd[mini->i][i]))
			i++;
		else
			ft_putchar(mini->scmd[mini->i][i++]);
	}
	ft_putchar('\n');
	return (0);
}
