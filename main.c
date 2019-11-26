/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:37:15 by bpole             #+#    #+#             */
/*   Updated: 2019/11/26 10:40:07 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		init_env(t_st *st, char **envv)
{
	int			i;
	char        *tmp;

	st->len_env = 0;
	st->tmp = ft_strnew(PATH_MAX);
	while (envv[st->len_env])
		st->len_env++;
	st->env = (char**)ft_memalloc(sizeof(char*) * (st->len_env + 1));
	i = 0;
	while (envv[i])
	{
		st->env[i] = ft_strdup(envv[i]);
		if (ft_strnequ(st->env[i], "PATH=", 5))
			st->path_bin = ft_strsplit(st->env[i] + 5, ':');
		i++;
	}
	tmp = find_env_valiable(st, "HOME=");
    st->old_dir = ft_strdup(tmp);
}

static void		output_invitation(void)
{
	char		buff[BUFF_PATH + 1];
	char		*path;
	char		**arr;
	int			i;

	i = 0;
	path = getcwd(buff, BUFF_PATH);
	arr = ft_strsplit(path, '/');
	while (arr && arr[i])
		i++;
	if (arr && i && arr[i - 1])
		ft_printf(MAG"%s > "RESET, arr[i - 1]);
	else
		ft_printf(MAG"/ > "RESET);
	ft_free_char_arr(&arr);
}

static void		handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		output_invitation();
		signal(SIGINT, handler);
	}
}

static int		read_line(t_st *st)
{
	st->line = NULL;
	get_next_line(0, &st->line);
	if (st->line)
		return (0);
	ft_putstr("\n");
	return (1);
}

int				main(int ac, char **av, char **envv)
{
	t_st		st;

	ft_bzero(&st, sizeof(t_st));
	st.env = NULL;
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
	free_st(&st);
	(void)ac;
	(void)av;
	return (0);
}
