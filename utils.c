/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:42:28 by bpole             #+#    #+#             */
/*   Updated: 2019/11/25 17:28:03 by bpole            ###   ########.fr       */
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
    if (st->old_dir)
        free(st->old_dir);
}

char		*find_env_valiable(t_st *st, char *env_variable)
{
    int         len;
    int			i;

    len = ft_strlen(env_variable);
    i = 0;
    while (st->env[i])
    {
        if (ft_strnequ(st->env[i], env_variable, len))
            return(st->env[i] + len);
        i++;
    }
    ft_printf(RED"variable \"%.*s\" not found"RESET"\n", len - 1, env_variable);
    return (NULL);
}