/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:42:28 by bpole             #+#    #+#             */
/*   Updated: 2019/11/23 23:43:15 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_free_char_arr(char ***arr)
{
	int		i;

	i = 0;
	if (*arr)
	{
		while ((*arr)[i])
			ft_strdel(&((*arr)[i++]));
		free(*arr);
		*arr = NULL;
	}
}

void		free_st(t_st *st)
{
	ft_free_char_arr(&st->env);
	ft_free_char_arr(&st->commands);
	ft_free_char_arr(&st->path_bin);
	if (st->tmp)
		free(st->tmp);
}
