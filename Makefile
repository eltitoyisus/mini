# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 20:02:00 by jramos-a          #+#    #+#              #
#    Updated: 2025/05/16 15:07:55 by daniel-cast      ###   ########.fr        #
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
		$(SRC_DIR)parse_cmd.c		\
		$(SRC_DIR)lsts_sh.c			\
		$(SRC_DIR)frees.c			\
		$(SRC_DIR)utils.c			\
		$(SRC_DIR)tx.c				\
		$(SRC_DIR)identifiers.c		\

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

.PHONY: all clean fclean re
