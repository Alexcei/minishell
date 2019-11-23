#include "minishell.h"

static void		add_variable_to_env(char **com, t_st *st)
{
	char		**new_env;
	int 		i;

	new_env = (char**)ft_memalloc(sizeof(char*) * (++st->len_env + 1));
	i = 0;
	while (st->env[i])
	{
		new_env[i] = ft_strdup(st->env[i]);
		i++;
	}
	if (st->count_args > 2)
		new_env[i] = ft_strdup(ft_strcat(st->tmp, com[2]));
	else
		new_env[i] = ft_strdup(st->tmp);
	ft_free_char_arr(&st->env);
	st->env = new_env;
}

static void		chang_variable(char **com, int i, t_st *st)
{
	char		 *tmp;

	tmp = st->env[i];
	if (st->count_args > 2)
		st->env[i] = ft_strdup(ft_strcat(st->tmp, com[2]));
	else
		st->env[i] = ft_strdup(st->tmp);
	free(tmp);
}

static void		find_changing_variable(char **com, t_st *st)
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
			chang_variable(com, i, st);
			return ;
		}
		i++;
	}
	add_variable_to_env(com, st);
}

void			do_setenv(char **com, t_st *st)
{
	count_args(com, st);
	if (st->count_args > 3)
		ft_printf("setenv: too many arguments.\n");
	find_changing_variable(com, st);
}