/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:37:31 by bpole             #+#    #+#             */
/*   Updated: 2019/11/26 12:38:28 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		open_dir(char *dir, t_st *st)
{
	char		buff[BUFF_PATH + 1];
	char		*path;

	path = getcwd(buff, BUFF_PATH);
	if (!chdir(dir))
	{
		ft_strdel(&st->old_dir);
		st->old_dir = ft_strdup(path);
	}
	else if (access(dir, F_OK) == -1)
		ft_printf(RED"cd: no such file or directory: %s"RESET"\n", dir);
	else if (access(dir, R_OK) == -1)
		ft_printf(RED"cd: permission denied: %s"RESET"\n", dir);
	else
		ft_printf(RED"cd: not a directory: %s"RESET"\n", dir);
}

void			do_cd(char **com, t_st *st)
{
	count_args(com, st);
	if (st->count_args == 1)
		open_dir(find_env_valiable(st, "HOME="), st);
	else if (st->count_args > 3)
		ft_printf(RED"cd: too many arguments"RESET"\n");
	else if (st->count_args > 2)
		ft_printf(RED"cd: string not in pwd: %s"RESET"\n", com[1]);
	else
	{
		if (ft_strequ(com[1], "~"))
			open_dir(find_env_valiable(st, "HOME="), st);
		else if (ft_strequ(com[1], "-"))
			open_dir(st->old_dir, st);
		else if (com[1][0] == '~')
		{
			ft_strclr(st->tmp);
			ft_strcat(st->tmp, find_env_valiable(st, "HOME="));
			ft_strcat(st->tmp, com[1] + 1);
			open_dir(st->tmp, st);
		}
		else
			open_dir(com[1], st);
	}
}
