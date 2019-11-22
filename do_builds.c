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