# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 20:02:00 by jramos-a          #+#    #+#              #
#    Updated: 2025/06/18 10:22:06 by daniel-cast      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Werror -Wall -Wextra -g3
LDFLAGS = -lreadline -lhistory
NAME = minishell
RM = rm -rf
SRC_DIR = src/
SNK_DIR = tan/
RED=\033[0;31m
YELLOW=\033[0;33m
NC=\033[0m

SNK = $(SNK_DIR)tin.c						\
		$(SNK_DIR)tin_2.c					\
		$(SNK_DIR)utils_tin.c				\


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

OBJ = $(SRC:.c=.o) $(SNK:.c=.o)

all: $(NAME)

	@echo ""
	@echo "        .       .    )        .           ."
	@echo "   .       *             .         ."
	@echo "                 .                      ."
	@echo "   .       .       .'          ."
	@echo "                  '.              *        ."
	@echo "      .   '        .'     .              ."
	@echo "              _.---._   .            .     *"
	@echo "    *       .'       '."
	@echo "        _.-~===========~-._"
	@echo "       (___________________)       .   *"
	@echo "  __         \_______/       ______        __"
	@echo "    |                       |      |      |  |"
	@echo "    |                       |      |      |  |"
	@echo "    |                       |      |   ___|  |_"
	@echo "  __|_______________________|__..--~~~~ jro    ~-- "
	@echo "                    /|\                  "
	@echo "                   /   \               "
	@echo "                  /  |  \               "
	@echo "                 /       \               "
	@echo "   \|/          /    |    \               "
	@echo "               /           \                    "
	@echo "              /      |      \                   "
	@echo "             /               \               "
	@echo "            /        |        \               "
	@echo "           /                                "
	@echo "          /   ____   |               "
	@echo "         /   /  __)         ___               "
	@echo "        /    \(~oo   |     (___)  /               "
	@echo "       /     _\_-/_       (_o o_)               "
	@echo "      /     /  \/  \ |    (_\O/_)   \               "
	@echo "     /     / /    \ \     //\_/\\    \               "
	@echo "    /      \ |    /_/    //(_ _)\\    \               "
	@echo "   /        \|___(_/     \\/   \//     \    \|/               "
	@echo "             |    \      (/_____\)            "
	@echo "             | |\  \      / /| |            "
	@echo "             | |/  /      \ \| |            "
	@echo "             |_/__/        \_|_|            "
	@echo "            (__[__)        <_<_>            "
	@echo "                                                "
	@echo "  * * * * * * * * * * * * * * * * * * * * * * * * "
	@echo "   * * * * * * * * * * * * * * * * * * * * * * * *"
	@sleep 1

	@clear
	@echo "         .                            *                 "
	@echo "                   _.--~~~~--._                 "
	@echo "     .          .-~ \__/  \__/ ~-.         .                 "
	@echo "              .-~   (oo)  (oo)    ~-.                 "
	@echo "             (_____//~~\\//~~\\______)                 "
	@echo "        _.-~/                        \~-._                 "
	@echo "       /O=O=O=O=O=O=O=O=O=O=O=O=O=O=O=O=O=O\                 "
	@echo "       \___________________________________/                 "
	@echo "                  \x x x x x x x/                 "
	@echo "                   \x_x_x_x_x_x/                 "
	@echo "                    :|. | | .|                 "
	@echo "                    | |. |. |:| Zzuzz!                 "
	@echo "                    | :  |:. ;|                 "
	@echo "   Ohmygosh, a     . | : .|  :                   "
	@echo "   flying saucer!   | . | : .||                 "
	@echo "   - !Delores! -   : |. | . ::  Zzuzz!                 "
	@echo "       \    ___     |.: |. :. |                 "
	@echo "           /  _)    | :|___ |:|                 "
	@echo "          |  (~o   (\.|(___)  /)                 "
	@echo "          _\/_/_    \\(_O O_)//   Zzuzz!                 "
	@echo "         /      \   .\(_\O/_)/:                 "
	@echo "        / /    \ \  :|\/\_/\/ |                 "
	@echo "        \ |    | /  | .(_ _): |                 "
	@echo "         \|____|/   .| /   \ |:                 "
	@echo "          |_  _|    | /_____\.| !!!EEEEKKKK!!!                 "
	@echo "          | |  |    : .| | | .                 "
	@echo "          | |  |    .  | | | ||                 "
	@echo "          |_|__|    | :|_|_| .:                 "
	@echo "  jro     [__[__)   .: <_|_> .|                 "
	@echo "                                                   "
	@echo " jrojrojrojrojrojrojrojrojrojrojrojrojrojrojro                 "
	@echo " jrojrojrojrojrojrojrojrojrojrojrojrojrojrojro                 "
	@sleep 1


	@clear
	@echo "     .       .    )        .           .                      "
	@echo "  .       *             .         .                      "
	@echo "              .                      .                      "
	@echo "  .       .                   .                      "
	@echo "                               *        .                      "
	@echo "     .   '               .              .                      "
	@echo "             _.---._   .            .     *                      "
	@echo "   *       .'       '.                      "
	@echo "       _.-~===========~-._                      "
	@echo "      (___________________)       .   *                      "
	@echo " __  .'     \_______/   .'  ______        __                      "
	@echo "   |              .'  .'   |      |      |  |                      "
	@echo "   |             '         |      |      |  |                      "
	@echo "   |                       |      |   ___|  |_                      "
	@echo " __|_______________________|__..--~~~~ jro    ~--.                      "
	@echo "                   /|\                      "
	@echo "                  /   \                      "
	@echo "                 /  |  \                      "
	@echo "                /       \                      "
	@echo "  \|/          /    |    \                      "
	@echo "              /           \                      "
	@echo "             /      |      \                      "
	@echo "            /               \                      "
	@echo "           /                                "
	@echo "          /       BRING MY WIFE BACK,                      "
	@echo "         /    __  YOU COSMIC KIDNAPPERS!                      "
	@echo "        /    /  \ /                      "
	@echo "       /    (\__/)  |            \                      "
	@echo "      /     _\__/_                \                      "
	@echo "     /     /      \ |              \                      "
	@echo "    /     / /   / /                 \                      "
	@echo "          \ |   \_\                  \                      "
	@echo "           \|____\_)                  \    \|/                      "
	@echo "            |    \                      "
	@echo "            | |\  \                      "
	@echo "            | |/  /                      "
	@echo "            |_/__/                      "
	@echo "           (__[__)                      "
	@echo "                                         "
	@echo " 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8                      "
	@echo "  8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8   "
	@sleep 1


	@clear
	@echo "	        .       .    )        .           .                "
	@echo "   .       *             .         .                "
	@echo "                 .                      .                "
	@echo "   .       .          o        .                "
	@echo "                    ..            *        .                "
	@echo "      .   .       ..      .              .                "
	@echo "  __        .   ..           ______        __                "
	@echo "    |           ..          |      |      |  |                "
	@echo "    |            ..         |      |      |  |                "
	@echo "    |                       |      |   ___|  |_                "
	@echo "  __|_______________________|__..--~~~~ jro    ~--                "
	@echo "                    /|\                "
	@echo "                   /   \                "
	@echo "                  /  |  \                "
	@echo "                 /       \                "
	@echo "   \|/          /    |    \                "
	@echo "               /           \                "
	@echo "              /      |      \                "
	@echo "             /               \                "
	@echo "            /        |        \                "
	@echo "           /   _               \                "
	@echo "          /   /_\    |          \                "
	@echo "         /    \_/                \                "
	@echo "        /    /   \   |            \                "
	@echo "       /     \|_|/                 \                "
	@echo "      /       |||    |              \                "
	@echo "     /        |||                    \                "
	@echo "    /        (_|_)   |                \                "
	@echo "   /                                   \    \|/                "
	@echo "                "
	@echo "  # # # # # # # # # # # # # # # # # # # # # # # #                "
	@echo "   # # # # # # # # # # # # # # # # # # # # # # # #                "
	@sleep 1

	@clear
	@echo " "
	@echo " "
	@echo " "
	@echo " ░░░░░░░░░░░░░░░░░░░$(YELLOW)▄▄$(NC)░░░░░░░░░░░░░░░░░░░          ██████ ██████  ██ ██████  ████████  ██████  ███████ ██   ██ ███████ ██      ██                 "
	@echo " ░░░░░░░░░░░░░░░░░$(YELLOW)▄▄██▄▄$(NC)░░░░░░░░░░░░░░░░░         ██      ██   ██ ██ ██   ██    ██    ██    ██ ██      ██   ██ ██      ██      ██                 "
	@echo " ░░░░░░░░░░░░░░░░░$(YELLOW)▀▀██▀▀$(NC)░░░░░░░░░░░░░░░░░         ██      ██████  ██ ██████     ██    ██    ██ ███████ ███████ █████   ██      ██                 "
	@echo " ░░░░░░░░$(YELLOW)▄▄▄███████▄██▄███████▄▄▄$(NC)░░░░░░░░         ██      ██   ██ ██ ██         ██    ██    ██      ██ ██   ██ ██      ██      ██                 "
	@echo " ░░░░$(YELLOW)▄█████▀▄$(NC)░░$(YELLOW)▀$(NC)░░$(YELLOW)██████$(NC)░░$(YELLOW)▀$(NC)░░$(YELLOW)▄▀█████▄$(NC)░░░░          ██████ ██   ██ ██ ██         ██     ██████  ███████ ██   ██ ███████ ███████ ███████                 "
	@echo " ░░$(YELLOW)▄█▀▀░$(YELLOW)██$(NC)░░░░░░░░░░$(YELLOW)██▀$(NC)░░░░░░░░░$(YELLOW)██$(NC)░$(YELLOW)▀▀█▄$(NC)░░                          "
	@echo " ░$(YELLOW)██░░$(YELLOW)▄██▀▀$(NC)░░░░░░░░░$(YELLOW)██$(NC)░░░░░░░░░$(YELLOW)▀▀██▄$(NC)░$(YELLOW)▀██$(NC)░                          "
	@echo " $(YELLOW)██░░░░$(YELLOW)██$(NC)░░░░░░░░░░░$(YELLOW)██$(NC)░░░░░░░░░░░$(YELLOW)██$(NC)░░░░$(YELLOW)██$(NC)                          "
	@echo " $(YELLOW)██░$(YELLOW)█$(NC)░░$(YELLOW)██▀▀$(NC)░░░░░░░░░$(YELLOW)██$(NC)░░░░░░░░░$(YELLOW)▀▀██$(NC)░░$(YELLOW)█░$(NC)$(YELLOW)██$(NC)                          "
	@echo " $(YELLOW)██░░░░$(YELLOW)▀██▄$(NC)░░░░░░░░░$(YELLOW)██$(NC)░░░░░░░░░$(YELLOW)▄██▀$(NC)░░░░$(YELLOW)██$(NC)                          "
	@echo " ░$(YELLOW)██░$(YELLOW)▀$(NC)░░$(YELLOW)▀██▀$(NC)░░░░░░$(YELLOW)▄████▄$(NC)░░░░░░$(YELLOW)▀▄█▀$(NC)░░$(YELLOW)▀$(NC)░$(YELLOW)██$(NC)░                          "
	@echo " ░$(YELLOW)▀██░░$(YELLOW)▄$(NC)░$(YELLOW)▀██▀▄$(NC)░░░░$(YELLOW)██▄▄██$(NC)░░░░$(YELLOW)▄▀██▀$(NC)░$(YELLOW)▄$(NC)░$(YELLOW)▄██▀$(NC)░                          "
	@echo " ░░░$(YELLOW)██▄▄▄▄██████████████████████▄▄▄▄█▀░$(NC)░░                          "
	@echo " ░░░░$(YELLOW)█▀▀▀▀▀▀░░$(YELLOW)▄▄▄▄▄░░░░$(YELLOW)▄▄▄▄▄░░$(YELLOW)▀▀▀▀▀▀█$(NC)░░░░            DACASTIL && JRAMOS-A              "
	@echo " ░░░░░$(YELLOW)███░░░░░$(YELLOW)▀███░░░░░░$(YELLOW)███▀░░░░░$(YELLOW)███$(NC)░░░░░                          "
	@echo " ░░░░░$(YELLOW)▀██▄░░░░$(YELLOW)▀▀▀▀▀░░░░$(YELLOW)▀▀▀▀▀░░░░$(YELLOW)▄██▀$(NC)░░░░░                          "
	@echo " ░░░░░$(YELLOW)▄▄▄▄██████████████████████▄▄▄▄$(NC)░░░░░                          "
	@echo " ░░░░░░$(YELLOW)▀▀▀▀$(NC)░░░░░░░░░░░░░░░░░░░░$(YELLOW)▀▀▀▀$(NC)░░░░░░                          "


libft/libft.a:
	@$(MAKE) -C libft > /dev/null 2>&1

$(NAME): $(OBJ) libft/libft.a
	@$(CC) $(FLAGS) $(OBJ) libft/libft.a -o $(NAME) $(LDFLAGS) > /dev/null 2>&1

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ) > /dev/null 2>&1
	@$(MAKE) clean -C libft > /dev/null 2>&1

fclean:

	@clear
	@echo ""
	@echo "$(RED) █▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█"
	@echo "$(RED) █░██░██░██░██░██░██░██░██░██░░░░░░░░░░█"
	@echo "$(RED) █░██░██░██░██░██░██░██░██░██░░░░░░░░░░█"
	@echo "$(RED) █▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█"
	@echo "$(RED) "
	@echo "$(RED)  █    █▀▀▀█ █▀▀█ █▀▀▄ ▀█▀ █▄  █ █▀▀█"
	@echo "$(RED)  █    █   █ █▄▄█ █  █  █  █ █ █ █ ▄▄"
	@echo "$(RED)  █▄▄█ █▄▄▄█ █  █ █▄▄▀ ▄█▄ █  ▀█ █▄▄█"
	@echo "$(RED) "
	@sleep 0.5

	@clear
	@echo ""
	@echo "$(RED)█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█"
	@echo "$(RED)█░██░██░██░██░██░██░██░██░██░██░░░░░░░█"
	@echo "$(RED)█░██░██░██░██░██░██░██░██░██░██░░░░░░░█"
	@echo "$(RED)█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█"
	@echo "$(RED)"
	@echo "$(RED) █    █▀▀▀█ █▀▀█ █▀▀▄ ▀█▀ █▄  █ █▀▀█"
	@echo "$(RED) █    █   █ █▄▄█ █  █  █  █ █ █ █ ▄▄"
	@echo "$(RED) █▄▄█ █▄▄▄█ █  █ █▄▄▀ ▄█▄ █  ▀█ █▄▄█"
	@echo "$(RED)"
	@sleep 0.5

	@clear
	@echo ""
	@echo "$(RED)█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█"
	@echo "$(RED)█░██░██░██░██░██░██░██░██░██░██░██░░░░█"
	@echo "$(RED)█░██░██░██░██░██░██░██░██░██░██░██░░░░█"
	@echo "$(RED)█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█"
	@echo "$(RED)"
	@echo "$(RED) █    █▀▀▀█ █▀▀█ █▀▀▄ ▀█▀ █▄  █ █▀▀█"
	@echo "$(RED) █    █   █ █▄▄█ █  █  █  █ █ █ █ ▄▄"
	@echo "$(RED) █▄▄█ █▄▄▄█ █  █ █▄▄▀ ▄█▄ █  ▀█ █▄▄█"
	@echo "$(RED)"
	@sleep 0.5

	@clear
	@echo ""
	@echo "$(RED)█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█"
	@echo "$(RED)█░██░██░██░██░██░██░██░██░██░██░██░██░█"
	@echo "$(RED)█░██░██░██░██░██░██░██░██░██░██░██░██░█"
	@echo "$(RED)█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█"
	@echo "$(RED)"
	@echo "$(RED) █    █▀▀▀█ █▀▀█ █▀▀▄ ▀█▀ █▄  █ █▀▀█"
	@echo "$(RED) █    █   █ █▄▄█ █  █  █  █ █ █ █ ▄▄"
	@echo "$(RED) █▄▄█ █▄▄▄█ █  █ █▄▄▀ ▄█▄ █  ▀█ █▄▄█"
	@echo "$(RED)$(NC)"

	@$(RM) $(OBJ) $(NAME) > /dev/null 2>&1
	@$(MAKE) fclean -C libft > /dev/null 2>&1

re: fclean all

v: re
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=readline.supp ./$(NAME)

vn:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=readline.supp ./$(NAME)

.PHONY: all clean fclean re
