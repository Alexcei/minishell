cmake_minimum_required(VERSION 3.14)
project(my_minishell C)

file(GLOB FILES
        "*.c"
        "*.h"
        "ft_printf/*.c"
        "ft_printf/ft_printf.h"
        "ft_printf/libft/*.c"
        "ft_printf/libft/libft.h")

set(CMAKE_C_STANDARD 99)
add_definitions(-Wall -Wextra -Werror)
add_executable(my_minishell ${FILES} double_split.c do_cd.c)