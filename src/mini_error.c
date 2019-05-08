/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:43:16 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/07 20:22:17 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			dis_error(int error)
{
	if (error == W_SETENV)
	{
		ft_printf("87SHELL: setenv: Invalid option\n");
		ft_printf("setenv  NAME  VALUE\n");
	}
	else if (error == W_UNSET)
	{
		ft_printf("87SHELL: unsetenv: Invalid option\n");
		ft_printf("unsetenv  NAME\n");
	}
}
