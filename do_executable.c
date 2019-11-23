#include "minishell.h"

static void			built_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		signal(SIGINT, built_handler);
	}
}

static int			run_process(char **com, t_st *st)
{
	pid_t			pid;

	pid = fork();
	signal(SIGINT, built_handler);
	if (pid == 0)
	{
		if (execve(st->tmp, com, st->env) == -1)
			return (1);
	}
	else if (pid < 0)
		ft_fprintf(1, "failed to fork.\n");
	else
		wait(&pid);
	return (1);
}

static int			check_executable(char **com, char *executable, t_st *st)
{
	int 			i;
	struct stat		stats;

	i = 0;
	while (st->path_bin[i])
	{
		ft_bzero(st->tmp, ft_strlen(st->tmp));
		ft_strcat(st->tmp, st->path_bin[i]);
		ft_strcat(st->tmp, "/");
		ft_strcat(st->tmp, executable);
		if (access(st->tmp, F_OK) != -1 && lstat(st->tmp, &stats) != -1)
		{
			if (stats.st_mode & S_IXUSR)
				return (run_process(com, st));
			else
				ft_fprintf(1, RED"minishell: permission denied: %s.\n"RESET, executable);
		}
		i++;
	}
	return (0);
}

int 				do_executable_process(char **com, char *executable, t_st *st)
{
	struct stat		stats;

	if (executable[0] == '.' && executable[1] == '/' &&
		lstat(executable, &stats) != -1 && stats.st_mode & S_IXUSR)
		return (run_process(com, st));
	if (check_executable(com, executable, st))
		return (1);
	return (0);
}