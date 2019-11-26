# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bpole <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 10:08:31 by bpole             #+#    #+#              #
#    Updated: 2019/11/25 15:22:25 by bpole            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIB_DIR = ./ft_printf/

LIBFT = $(LIB_DIR)libftprintf.a

SRC = main.c do_builds.c utils.c do_unsetenv.c do_setenv.c \
        do_executable.c parse.c double_split.c do_cd.c fork_process.c

OBJ = $(SRC:.c=.o)

INCLUDE = ./

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	$(CC) -c $(FLAGS) $<

$(NAME): $(OBJ)
	$(MAKE) -C $(LIB_DIR)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)

clean:
	rm -rf $(OBJ)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all