/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_help2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 13:30:07 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/10 08:21:56 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_word_count(const char *s)
{
	size_t		len;
	size_t		i;

	len = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (ft_isspace(s[i]))
			i++;
		if (s[i] != '\0' && !(ft_isspace(s[i])))
			len++;
		while (s[i] != '\0' && !(ft_isspace(s[i])))
			i++;
	}
	return (len);
}

static int	ft_word_len(const char *s)
{
	size_t		len;
	size_t		i;

	i = 0;
	len = 0;
	while (ft_isspace(s[i]))
		i++;
	while (s[i] != '\0' && !(ft_isspace(s[i])))
	{
		i++;
		len++;
	}
	return (len);
}

char		**mini_split(const char *s)
{
	int		i;
	int		j;
	int		l;
	char	**new_s;

	if (!s || !(new_s = (char **)malloc(sizeof(char *) *
					(ft_word_count(s) + 1))))
		return (0);
	i = 0;
	j = 0;
	while (i < ft_word_count(s))
	{
		l = 0;
		if (!(new_s[i] = ft_strnew((ft_word_len(&s[j] + 1)))))
			return (0);
		while (ft_isspace(s[j]))
			j++;
		while (s[j] != '\0' && !(ft_isspace(s[j])))
			new_s[i][l++] = s[j++];
		new_s[i][l] = '\0';
		i++;
	}
	new_s[i] = NULL;
	return (new_s);
}
