/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:30:03 by bpole             #+#    #+#             */
/*   Updated: 2019/11/24 00:50:25 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			do_help(void)
{
	ft_putstr(CYN"The following commands are available:\n"RESET);
	ft_putstr(GRN"help\n");
	ft_putstr("echo\n");
	ft_putstr("env\n");
	ft_putstr("setenv\n");
	ft_putstr("unsetenv\n");
	ft_putstr("cd\n");
	ft_putstr("exit.\n"RESET);
}

void			do_env(char **env)
{
	while (*env)
		ft_printf("%s\n", *env++);
}

void			do_echo(char *com)
{
	if (!com)
		return ;
	ft_putstr(com);
	ft_putstr("\n");
}

static void		find_home(t_st *st)
{
	int			i;

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

void			do_cd(char **com, t_st *st)
{
	count_args(com, st);
	if (!chdir(com[1]))
		return ;
	if (st->count_args > 3)
		ft_printf(RED"cd: too many arguments.\n"RESET);
	else if (st->count_args > 2)
		ft_printf(RED"cd: string not in pwd: %s.\n"RESET, com[1]);
	else if (com[1])
	{
		if (ft_strequ(com[1], "~"))
			find_home(st);
		else if (access(com[1], F_OK) == -1)
			ft_printf(RED"cd: no such file or directory: %s.\n"RESET, com[1]);
		else if (access(com[1], R_OK) == -1)
			ft_printf(RED"cd: permission denied: %s.\n"RESET, com[1]);
		else
			ft_printf(RED"cd: not a directory: %s.\n"RESET, com[1]);
	}
}
