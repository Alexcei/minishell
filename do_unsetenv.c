#include "minishell.h"

void			count_args(char **com, t_st *st)
{
	st->count_args = 0;
	while (com[st->count_args])
		st->count_args++;
}

static void		del_variable(int i, t_st *st)
{
	char	**new_env;
	int 	len;
	int 	len_old;

	new_env = (char**)ft_memalloc(sizeof(char*) * (--st->len_env + 1));
	len = 0;
	len_old = 0;
	while (st->env[len_old])
	{
		if (len == i)
			i--;
		else
		{
			new_env[len] = ft_strdup(st->env[len_old]);
			len++;
		}
		len_old++;
	}
	ft_free_char_arr(&st->env);
	st->env = new_env;
}

static int		find_and_del_variable(char **com, t_st *st)
{
	int 		i;

	i = 0;
	ft_bzero(st->tmp, ft_strlen(st->tmp));
	ft_strcat(st->tmp, com[1]);
	ft_strcat(st->tmp, "=");
	while (st->env[i])
	{
		if (ft_strnequ(st->env[i], st->tmp, ft_strlen(st->tmp)))
		{
			del_variable(i, st);
			return (0);
		}
		i++;
	}
	return (1);
}

void 			do_unsetenv(char **com, t_st *st)
{
	count_args(com, st);
	if (st->count_args > 2)
		ft_printf("unsetenv: too many arguments.\n");
	else if (st->count_args == 1)
		ft_printf("unsetenv: too few arguments.\n");
	else
	{
		if (find_and_del_variable(com, st))
			ft_printf("unsetenv: variable not found: %s.\n", com[1]);
	}
}