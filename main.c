#include "minishell.h"

void	init_env(t_st *st, char **envv)
{
	char	buff[BUFF_CWD + 1];
	int 	len;

	len = 0;
	st->path = getcwd(buff, BUFF_CWD);
	while (envv[len])
		len++;
	st->env = (char**)ft_memalloc((sizeof(char*) * len) + 1);
	len = 0;
	while (envv[len])
	{
		st->env[len] = ft_strdup(envv[len]);
		len++;
	}
}

int		run_process(char **com, char *executable, t_st *st)
{
	pid_t	pid;

	pid = fork();
	signal(SIGINT, handler);  // ?????????????????
	if (pid == 0)
	{
		ft_printf("%s %s\n", st->path, com[0]);
		if (execve(st->path, com, st->env) == -1)
			ft_fprintf(1, executable, "permission denied");
	}
	else if (pid < 0)
		ft_fprintf(1, executable, "failed to fork");
	else
		wait(&pid);
	return (1);
}

int 	is_executable_process(char **com, char *executable, t_st *st)
{
	struct stat		stats;

	if (executable[0] == '.' && executable[1] == '/' &&
	lstat(executable, &stats) != -1 && stats.st_mode & S_IXUSR)
		return (run_process(com, executable + 2, st));
	/*else if (access(executable + 2, F_OK))
	{
		if (lstat(executable + 2, &stats) != -1 && stats.st_mode & S_IXUSR)
			return (run_process(com, executable + 2, st));
	}*/
	return (0);
}

int		apply_command(char **com, char *command, t_st *st)
{
	if (is_executable_process(com, com[0], st))
		return (0);
	else if (ft_strequ(com[0], "exit"))
		return (1);
	else if (ft_strequ(com[0], "help"))
		do_help();
	else if (ft_strequ(com[0], "echo"))
		(do_echo(command + 5));
	else if (ft_strequ(com[0], "env"))
		do_env(st->env);
	else
		ft_putstr("./minishell: command not found\n");
	return (0);
}

int 	parse_com(char *command, t_st *st)
{
	char	**com;

	com = ft_strsplit(command, ' ');
	if (com[0])
	{
		if (apply_command(com, command, st))
		{
			ft_free_char_arr(com);
			return (1);
		}
	}
	ft_free_char_arr(com);
	return (0);
}

int 	parse_commands(t_st *st) //(char **line, char **env)
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

int		main(int ac, char **av, char **envv)
{
	t_st	st;

	ft_bzero(&st, sizeof(t_st));
	init_env(&st, envv);
	while (21)
	{
		output_invitation();
		signal(SIGINT, handler);
		if (read_line(&st))
			continue ;
		if (parse_commands(&st))
			break ;
	}
	ft_free_char_arr(st.env);
	(void)ac;
	(void)av;
	return (0);
}