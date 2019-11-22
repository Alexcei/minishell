#include "minishell.h"

void	ft_free_char_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
		ft_strdel(&arr[i++]);
	free(arr);
}

void	output_invitation()
{
	char	buff[BUFF_CWD + 1];
	char	*path;
	char 	**arr;
	int 	i;

	i = 0;
	path = getcwd(buff, BUFF_CWD);
	arr = ft_strsplit(path, '/');
	while (arr[i])
		i++;
	ft_putstr(arr[i -1]);
	ft_putstr(" > ");
	ft_free_char_arr(arr);
}

int		read_line(t_st *st)
{
	get_next_line(0, &st->line);
	if (st->line)
		return (0);
	ft_putstr("\n");
	return (1);
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		output_invitation();
		signal(SIGINT, handler);
	}
}