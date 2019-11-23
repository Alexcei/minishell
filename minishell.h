#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf/ft_printf.h"
# include <signal.h>
#include <sys/stat.h>
#include <limits.h>
# include <sys/wait.h>

typedef struct      s_st
{
	char 			**env;
	//char 			*path;
	char 			*line;
	char 			**commands;
	char			**path_bin;
	char 			*tmp;
	int				len_env;
	int 			count_args;
}                   t_st;

#define BUFF_PATH 4048

# define WHT	"\x1B[47m"
# define RESET	"\x1B[0m"

void	do_help(void);
void 	do_env(char **env);
void 	do_echo(char *com);
void	do_cd(char **com, char *command, t_st *st);
int 	do_executable_process(char **com, char *executable, t_st *st);

void	do_setenv(char **com, t_st *st);

void	count_args(char **com, t_st *st);
void 	do_unsetenv(char **com, t_st *st);

int 	parse_commands(t_st *st);

void		free_st(t_st *st);
void		ft_free_char_arr(char **arr);

#endif