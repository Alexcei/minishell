/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:25:03 by bpole             #+#    #+#             */
/*   Updated: 2019/11/26 12:25:26 by bpole            ###   ########.fr       */
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

int					run_process(char **com, char *executable, t_st *st)
{
	pid_t			pid;

	pid = fork();
	signal(SIGINT, built_handler);
	if (pid == 0)
	{
		if (execve(st->tmp, com, st->env) == -1)
		{
			ft_fprintf(1, RED"minishell: permission denied: %s"RESET"\n",
					executable);
			exit(1);
		}
	}
	else if (pid < 0)
		ft_fprintf(1, RED"failed to fork"RESET"\n");
	else
		wait(&pid);
	return (1);
}
