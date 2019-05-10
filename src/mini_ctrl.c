/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 08:46:21 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/10 08:21:07 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			set_ctrl(int signal)
{
	signal = 0;
	ft_putchar_fd('\n', 2);
	write(1, "\e[1;95m87SHELL> \e[0m", 20);
}

static void			set_nctrl(int signal)
{
	signal = 0;
	ft_putchar_fd('\n', 2);
}

void				mini_ctrl(void)
{
	signal(SIGTSTP, set_ctrl);
	signal(SIGINT, set_ctrl);
	signal(SIGQUIT, set_ctrl);
}

void				mini_nctrl(void)
{
	signal(SIGTSTP, set_nctrl);
	signal(SIGINT, set_nctrl);
	signal(SIGQUIT, set_nctrl);
}
