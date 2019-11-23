#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf/ft_printf.h"
# include <signal.h>
#include <sys/stat.h>
#include <limits.h>
# include <sys/wait.h>

#define BUFF_PATH 4048

typedef struct	s_st
{
	char 		**env;
	char 		*line;
	char 		**commands;
	char		**path_bin;
	char 		*tmp;
	int			len_env;
	int 		count_args;
}				t_st;

/*
**				do_builds.c
*/
void			do_help(void);
void			do_env(char **env);
void			do_echo(char *com);
void			do_cd(char **com, char *command, t_st *st);

/*
**				do_executable.c
*/
int				do_executable_process(char **com, char *executable, t_st *st);

/*
**				do_setenv.c
*/
void			do_setenv(char **com, t_st *st);

/*
**				do_unsetenv.c
*/
void			count_args(char **com, t_st *st);
void 			do_unsetenv(char **com, t_st *st);

/*
**				parse.c
*/
int				parse_commands(t_st *st);

/*
**				utils.c
*/
void			free_st(t_st *st);
void			ft_free_char_arr(char **arr);

#endif