/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 08:28:32 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/03 20:29:39 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <limits.h>

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"

typedef struct		s_mini
{
	char			**en;
	char			**Scmd;
	char			**cmd;
	char			**path;
}					t_mini;

typedef	struct		s_cmd
{
	char			*cm;
	void			(*fun)(char *, t_mini *);
}					t_cmd;

void				mini_exit(char *cmd, t_mini *mini);
void				mini_cd(char *cmd, t_mini *mini);
void				get_bin_path(char *bin, t_mini *mini);
void				mini_dsfree(char **str);
int					mini_command(t_mini *mini);
int					check_path(char *path);

#endif
