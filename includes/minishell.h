/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 08:28:32 by jchiang-          #+#    #+#             */
/*   Updated: 2019/05/10 12:00:36 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <limits.h>
# include <pwd.h>
# include <limits.h>
# include <sys/ioctl.h>

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"

# define W_SETENV	1
# define W_UNSET	2
# define W_NHOME	3
# define W_NOCMD	4
# define W_CDARG	5
# define W_FIPER	6
# define W_ECARG	7

# define E_HOME		1
# define E_PWD		2
# define E_OLDPWD	3
# define N_LINE		4

typedef	struct		s_path
{
	char			*pa;
	char			*va;
	struct s_path	*next;
}					t_path;

typedef struct		s_mini
{
	char			**en;
	char			**scmd;
	char			**cmd;
	char			**path;
	t_path			*ev;
	int				flag;
	int				i;
}					t_mini;

t_path				*mini_addlist(t_path *en, t_path *ev);
t_path				*mini_addpath(char *envp);
t_path				*mini_setenv(t_mini *mini);
t_path				*mini_unsetenv(t_mini *mini);
t_path				*mini_pathva(t_path *en, char *pa, char *va);
t_path				*mini_fix_help(int pa);
t_path				*mini_fixenv(t_mini *mini);
char				*mini_findpath(t_path *mini, char *str);
char				**mini_split(const char *s);
void				get_bin_path(char *bin, t_mini *mini);
void				dis_error(int error, char *msg);
void				mini_dsfree(char **str);
void				mini_dslist(t_mini *mini);
void				mini_cd(t_mini *mini);
void				mini_ctrl(void);
void				mini_nctrl(void);
void				mini_full_path(t_mini *mini);
int					mini_echo(t_mini *mini);
int					mini_rerror(int error, char *msg);
int					mini_chdir(char *path, char *name);
int					mini_jump(t_mini *mini);
int					mini_command(t_mini *mini);
int					mini_check_build(char *str);
int					mini_prquot(t_mini *mini, char *q, int i);
int					mini_dapr(t_mini *mini, char *q, int i);
int					check_path(t_mini *mini, char *path);

#endif
