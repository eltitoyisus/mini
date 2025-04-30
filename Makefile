# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 20:02:00 by jramos-a          #+#    #+#              #
#    Updated: 2025/04/30 19:13:27 by jramos-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Werror -Wall -Wextra -g3
LDFLAGS = -lreadline -lhistory
NAME = minishell
RM = rm -rf
SRC_DIR = src/

SRC = $(SRC_DIR)main.c				\
		$(SRC_DIR)error.c			\
		$(SRC_DIR)exec_command.c	\
		$(SRC_DIR)built_in.c		\
		$(SRC_DIR)built_in_env.c	\
		$(SRC_DIR)exec_built_in.c	\
		$(SRC_DIR)prompt.c			\
		$(SRC_DIR)inits.c			\
		$(SRC_DIR)factory.c			\
		$(SRC_DIR)signals.c			\
		$(SRC_DIR)parse.c			\
		$(SRC_DIR)pipes.c			\
		$(SRC_DIR)redirection.c		\
		$(SRC_DIR)free_shell.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

libft/libft.a:
	@$(MAKE) -C libft

$(NAME): $(OBJ) libft/libft.a
	@$(CC) $(FLAGS) $(OBJ) libft/libft.a -o $(NAME) $(LDFLAGS)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@$(MAKE) clean -C libft

fclean:
	@$(RM) $(OBJ) $(NAME)
	@$(MAKE) fclean -C libft

re: fclean all

v: re
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp ./$(NAME)

.PHONY: all clean fclean re
