#include "minishell.h"

void	do_help(void)
{
	ft_putstr("The following commands are available:\n");
	ft_putstr("help\n");
	ft_putstr("echo\n");
	ft_putstr("env\n");
	ft_putstr("setenv\n");
	ft_putstr("unsetenv\n");
	ft_putstr("cd\n");
	ft_putstr("exit\n");
}

void 	do_env(char **env)
{
	while (*env)
		ft_printf("%s\n", *env++);
}

void 	do_echo(char *com)
{
	if (!com)
		return ;
	ft_putstr(com);
	ft_putstr("\n");
}

static void		find_home(t_st *st)
{
	int 	i;

	i = 0;
	while (st->env[i])
	{
		if (ft_strnequ(st->env[i], "HOME=", 5))
		{
			chdir(st->env[i] + 5);
			return ;
		}
		i++;
	}
}

void	do_cd(char **com, char *command, t_st *st)
{
	count_args(com, st);
	if (!chdir(com[1]))
		return ;
	if (st->count_args > 3)
		ft_printf("cd: too many arguments\n");
	else if (st->count_args > 2)
		ft_printf("cd: string not in pwd: %s\n", com[1]);
	else if (com[1])
	{
		if (ft_strequ(com[1], "~"))
			find_home(st);
		else if (access(com[1], F_OK) == -1)
			ft_printf("cd: no such file or directory: %s\n", com[1]);
		else if (access(com[1], R_OK) == -1)
			ft_printf("permission denied: %s\n", com[1]);
		else
			ft_printf("cd: not a directory: %s\n", com[1]);
	}
	(void)command;
	(void)st;
}