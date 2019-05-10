/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:43:16 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/10 11:46:51 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				mini_rerror(int error, char *msg)
{
	if (error == W_FIPER)
	{
		ft_printf("87SHELL: Permission denied: %s\n", msg);
		return (0);
	}
	else if (error == W_ECARG)
	{
		ft_printf("Echo: Not Corret Number of Quote\n");
		return (0);
	}
	return (1);
}

void			dis_error(int error, char *msg)
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
	else if (error == W_NHOME)
		ft_printf("87SHELL: No HOME\n");
	else if (error == W_NOCMD)
		ft_printf("87SHELL: Command Not Found: %s\n", msg);
	else if (error == W_CDARG)
		ft_printf("cd : Invalid Number of Argument\n");
}
