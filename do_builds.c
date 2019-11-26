/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:30:03 by bpole             #+#    #+#             */
/*   Updated: 2019/11/26 12:40:37 by bpole            ###   ########.fr       */
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
	ft_putstr("exit\n"RESET);
}

void			do_env(char **env)
{
	while (*env)
		ft_printf("%s\n", *env++);
}

static int		put_env_variable(char *com, t_st *st)
{
	if (*com == '$' && *(com + 1))
	{
		ft_strclr(st->tmp);
		ft_strcat(st->tmp, com + 1);
		ft_strcat(st->tmp, "=");
		if (find_env_valiable(st, st->tmp))
		{
			ft_putstr(find_env_valiable(st, st->tmp));
			ft_putstr("\n");
		}
		return (1);
	}
	else
		return (0);
}

void			do_echo(char *com, t_st *st)
{
	while (*com && ft_isblank(*com))
		com++;
	com += 4;
	while (*com && ft_isblank(*com))
		com++;
	if (put_env_variable(com, st))
		return ;
	while (*com)
	{
		if (*com == 92 && *(com + 1))
		{
			if (*(com + 1) == 34 || *(com + 1) == 39)
			{
				ft_putchar(*(com + 1));
				com++;
			}
		}
		else if (*com != 34 && *com != 39)
			ft_putchar(*com);
		com++;
	}
	ft_putstr("\n");
}
