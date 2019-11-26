/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:39:18 by bpole             #+#    #+#             */
/*   Updated: 2019/11/26 12:18:19 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf/ft_printf.h"
# include <signal.h>
# include <sys/stat.h>
# include <limits.h>
# include <sys/wait.h>

# define BUFF_PATH 4048

# define CYN	"\x1B[36m"
# define RED	"\x1B[31m"
# define GRN	"\x1B[32m"
# define YEL	"\x1B[33m"
# define BLU	"\x1B[34m"
# define MAG	"\x1B[35m"
# define WHT	"\x1B[37m"
# define RESET	"\x1B[0m"

typedef struct	s_st
{
	char		**env;
	char		*line;
	char		**commands;
	char		**path_bin;
	char		*tmp;
	char        *old_dir;
	int			len_env;
	int			count_args;
}				t_st;

/*
**				do_builds.c
*/
void			do_help(void);
void			do_env(char **env);
void			do_echo(char *com, t_st *st);

/*
**				do_cd.c
*/
void			do_cd(char **com, t_st *st);

/*
**				do_executable.c
*/
int				do_executab_proc(char **com, char *executab, t_st *st);

/*
**				do_setenv.c
*/
void			do_setenv(char **com, t_st *st);

/*
**				do_unsetenv.c
*/
void			count_args(char **com, t_st *st);
void			do_unsetenv(char **com, t_st *st);

/*
**				double_split.c
*/
char			**ft_double_split(char const *s, char c1, char c2);

/*
**				fork_process.c
*/
int				run_process(char **com, char *executable, t_st *st);

/*
**				parse.c
*/
int				parse_commands(t_st *st);

/*
**				utils.c
*/
void			free_st(t_st *st);
void			ft_free_char_arr(char ***arr);
char		    *find_env_valiable(t_st *st, char *env_variable);

#endif
