#include "minishell.h"

void	ft_free_char_arr(char **arr)
{
	int		i;

	i = 0;
	if (arr && *arr)
	{
		while (arr[i])
			ft_strdel(&arr[i++]);
		free(arr);
	}
}

void		free_st(t_st *st)
{
	if (st->env && *(st->env))
		ft_free_char_arr(st->env);
	if (st->commands && *st->commands)
		ft_free_char_arr(st->commands);
	if (*st->path_bin)
		ft_free_char_arr(st->path_bin);
	if (st->tmp)
		free(st->tmp);
}