#include "minishell.h"

static int		apply_command(char **com, char *command, t_st *st)
{
	if (ft_strequ(com[0], "exit"))
		return (1);
	else if (ft_strequ(com[0], "help"))
		do_help();
	else if (ft_strequ(com[0], "echo"))
		do_echo(command + 5);
	else if (ft_strequ(com[0], "cd"))
		do_cd(com, command + 3, st);
	else if (ft_strequ(com[0], "env"))
		do_env(st->env);
	else if (ft_strequ(com[0], "setenv"))
		do_setenv(com, st);
	else if (ft_strequ(com[0], "unsetenv"))
		do_unsetenv(com, st);
	else if (do_executable_process(com, com[0], st))
		return (0);
	else
		ft_printf("zsh: command not found: %s\n", com[0]);
	return (0);
}

static int		parse_com(char *command, t_st *st)
{
	char	**com;

	com = ft_strsplit(command, ' ');
	if (com[0])
	{
		if (apply_command(com, command, st))
		{
			//ft_free_char_arr(com);
			return (1);
		}
	}
	ft_free_char_arr(com);
	return (0);
}

int 	parse_commands(t_st *st)
{
	int 	i;

	i = 0;
	st->commands = ft_strsplit(st->line, ';');
	free(st->line);
	while (st->commands[i])
	{
		if (parse_com(st->commands[i++], st))
		{
			ft_free_char_arr(st->commands);
			return (1);
		}
	}
	ft_free_char_arr(st->commands);
	return (0);
}