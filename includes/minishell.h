/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 08:28:32 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/07 20:23:45 by jchiang-         ###   ########.fr       */
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

# define W_SETENV	1
# define W_UNSET	2

typedef	struct		s_path
{
	char			*pa;
	char			*va;
	struct s_path	*next;
}					t_path;

typedef struct		s_mini
{
	char			**en;
	char			**Scmd;
	char			**cmd;
	char			**path;
	t_path			*ev;
}					t_mini;

t_path				*mini_addlist(t_path *en, t_path *ev);
t_path				*mini_addpath(char *envp);
t_path				*mini_setenv(t_mini *mini);
t_path				*mini_unsetenv(t_mini *mini);
void				mini_cd(char *cmd, t_mini *mini);
void				get_bin_path(char *bin, t_mini *mini);
void				dis_error(int error);
void				mini_dsfree(char **str);
void				mini_dslist(t_mini *mini);
int					mini_jump(t_mini *mini);
int					mini_command(t_mini *mini);
int					mini_check_build(t_mini *mini, char *str);
int					check_path(char *path);

#endif
