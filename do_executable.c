/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_executable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:32:45 by bpole             #+#    #+#             */
/*   Updated: 2019/11/26 00:53:22 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		{
			ft_fprintf(1, RED"minishell: permission denied: %s"RESET"\n",
					   st->tmp);
			exit(1);
		}
	}
	else if (pid < 0)
		ft_fprintf(1, RED"failed to fork"RESET"\n");
	else
		wait(&pid);
	return (1);
}

static int			set_path_bin(t_st *st)
{
	int			i;

	ft_free_char_arr(&st->path_bin);
	i = 0;
	while (st->env[i])
	{
		if (ft_strnequ(st->env[i], "PATH=", 5))
		{
			st->path_bin = ft_strsplit(st->env[i] + 5, ':');
			return (1);
		}
		i++;
	}
	return (0);
}

static int			check_executable(char **com, char *executable, t_st *st)
{
	int				i;
	struct stat		stats;

	i = 0;
	if (!set_path_bin(st))
		return (0);
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
				ft_fprintf(1, RED"minishell: permission denied: %s"RESET"\n",
						executable);
		}
		i++;
	}
	return (0);
}

int					do_executable_process(char **com,
										char *executable, t_st *st)
{
	struct stat stats;
	char		*path;
	char		buff[BUFF_PATH + 1];
	char		**arr;
	int			i;

	if (ft_strchr(executable, '/'))
	{
		path = getcwd(buff, BUFF_PATH);
		ft_bzero(st->tmp, ft_strlen(st->tmp));
		if (executable[0] == '/')
			ft_strcat(st->tmp, executable);
		else
		{
			ft_strcat(st->tmp, path);
			ft_strcat(st->tmp, "/");
			ft_strcat(st->tmp, executable);
		}

		if (access(executable, F_OK) != -1 && lstat(executable, &stats) != -1)
		{
			if (stats.st_mode & S_IXUSR)
				run_process(com, st);
			else
			{
				i = 0;
				arr = ft_strsplit(executable, '/');
				while (arr && arr[i])
					i++;
				if (arr && i && arr[i - 1])
					ft_fprintf(1, RED"minishell: permission denied: %s"RESET"\n",
						   arr[i - 1]);
				ft_free_char_arr(&arr);
			}
		}
		else
			ft_printf(RED"minishell: no such file or directory: %s"RESET"\n",
					executable);
		return (1);
	}
	else
	{
		if (check_executable(com, executable, st))
			return (1);
	}
	return (0);
}

/*
 * static void			built_handler(int sig)
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
		ft_fprintf(1, RED"failed to fork."RESET"\n");
	else
		wait(&pid);
	return (1);
}

static int			set_path_bin(t_st *st)
{
	int			i;

	ft_free_char_arr(&st->path_bin);
	i = 0;
	while (st->env[i])
	{
		if (ft_strnequ(st->env[i], "PATH=", 5))
		{
			st->path_bin = ft_strsplit(st->env[i] + 5, ':');
			return (1);
		}
		i++;
	}
	return (0);
}

static int			check_executable(char **com, char *executable, t_st *st)
{
	int				i;
	struct stat		stats;

	i = 0;
	if (!set_path_bin(st))
		return (0);
	while (st->path_bin[i])
	{
		ft_printf("%s\n", st->path_bin[i]);
		ft_bzero(st->tmp, ft_strlen(st->tmp));
		ft_strcat(st->tmp, st->path_bin[i]);
		ft_strcat(st->tmp, "/");
		ft_strcat(st->tmp, executable);
		if (access(st->tmp, F_OK) != -1 && lstat(st->tmp, &stats) != -1)
		{
			if (stats.st_mode & S_IXUSR)
				return (run_process(com, st));
			else
				ft_fprintf(1, RED"minishell: permission denied: %s."RESET"\n",
						executable);
		}
		i++;
	}
	return (0);
}

int					do_executable_process(char **com,
										char *executable, t_st *st)
{
	struct stat		stats;

	if (executable[0] == '.' && executable[1] == '/' &&
			lstat(executable, &stats) != -1 && stats.st_mode & S_IXUSR)
		return (run_process(com, st));
	if (check_executable(com, executable, st))
		return (1);
	return (0);
}
 */