#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf/ft_printf.h"
# include <signal.h>
#include <sys/stat.h>

typedef struct      s_st
{
	char 			**env;
	char 			*path;
	char 			*line;
	char 			**commands;
}                   t_st;

#define BUFF_CWD 4048

# define WHT	"\x1B[47m"
# define RESET	"\x1B[0m"

void	ft_free_char_arr(char **arr);
void	output_invitation();
int		read_line(t_st *st);
void	handler(int sig);

void	do_help(void);
void 	do_env(char **env);
void 	do_echo(char *com);

#endif