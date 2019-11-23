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