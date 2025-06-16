# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 20:02:00 by jramos-a          #+#    #+#              #
#    Updated: 2025/06/16 21:22:31 by jramos-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Werror -Wall -Wextra -g3
LDFLAGS = -lreadline -lhistory
NAME = minishell
RM = rm -rf
SRC_DIR = src/

SRC = $(SRC_DIR)main.c						\
		$(SRC_DIR)main_helper.c				\
		$(SRC_DIR)exec_command.c			\
		$(SRC_DIR)exec_command2.c			\
		$(SRC_DIR)exec_command3.c			\
		$(SRC_DIR)built_in.c				\
		$(SRC_DIR)built_in_env.c			\
		$(SRC_DIR)exec_built_in.c			\
		$(SRC_DIR)prompt.c					\
		$(SRC_DIR)inits.c					\
		$(SRC_DIR)factory.c					\
		$(SRC_DIR)signals.c					\
		$(SRC_DIR)parse.c					\
		$(SRC_DIR)parse2.c					\
		$(SRC_DIR)parse3.c					\
		$(SRC_DIR)parse4.c					\
		$(SRC_DIR)parse5.c					\
		$(SRC_DIR)lsts_sh.c					\
		$(SRC_DIR)frees.c					\
		$(SRC_DIR)frees2.c					\
		$(SRC_DIR)pipes.c					\
		$(SRC_DIR)pipes2.c					\
		$(SRC_DIR)pipes3.c					\
		$(SRC_DIR)pipes4.c					\
		$(SRC_DIR)pipes5.c					\
		$(SRC_DIR)pipes6.c					\
		$(SRC_DIR)pipes7.c					\
		$(SRC_DIR)pipes8.c					\
		$(SRC_DIR)redirection.c				\
		$(SRC_DIR)redirection2.c			\
		$(SRC_DIR)handle_redirs.c			\
		$(SRC_DIR)handle_redirs2.c			\
		$(SRC_DIR)handle_redirs3.c			\
		$(SRC_DIR)clean_redirs.c			\
		$(SRC_DIR)clean_redirs2.c			\
		$(SRC_DIR)heredoc.c					\
		$(SRC_DIR)heredoc_utils.c			\
		$(SRC_DIR)parse_cmd.c				\
		$(SRC_DIR)identifiers.c				\
		$(SRC_DIR)quotes.c					\
		$(SRC_DIR)quotes2.c					\
		$(SRC_DIR)random.c					\
		$(SRC_DIR)tx.c						\
		$(SRC_DIR)without_spaces.c			\
		$(SRC_DIR)utils_min.c				\
		$(SRC_DIR)build_command_args.c		\
		$(SRC_DIR)build_command_args2.c		\
		$(SRC_DIR)exec_command_args.c		\
		$(SRC_DIR)path.c					\
		$(SRC_DIR)get_path.c				\
		$(SRC_DIR)exec_external_command.c	\
		$(SRC_DIR)exec_external_command2.c	\
		$(SRC_DIR)process_redir.c			\
		$(SRC_DIR)exec_command_redirs.c		\
		$(SRC_DIR)exec_command_redirs2.c	\
		$(SRC_DIR)exec_builtin_redirs.c		\
		$(SRC_DIR)exec_pipe_chain.c			\
		$(SRC_DIR)exec_pipe_chain2.c		\
		$(SRC_DIR)case_no_space.c			\
		$(SRC_DIR)case_no_space2.c			\
		$(SRC_DIR)env_export.c				\
		$(SRC_DIR)env_cd.c					\
		$(SRC_DIR)exec_env.c				\
		$(SRC_DIR)env_echo.c				\
		$(SRC_DIR)utils.c					\
		$(SRC_DIR)utils2.c

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
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=readline.supp ./$(NAME)

vn:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=readline.supp ./$(NAME)

.PHONY: all clean fclean re
