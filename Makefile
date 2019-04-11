.PHONY: all clean fclean re
CC = clang
FLAGS = -c -Wall -Wextra -Werror -I Includes
FILENAMES = main.c additional_functions.c additional_functions2.c find_path.c parse.c
SRC = $(addprefix src/, $(FILENAMES))
LIB = libft/libft.a
SRO = $(SRC:.c=.o)
NAME = lem-in

all: $(SRC) $(NAME)

$(NAME): $(SRO) $(LIB)
	@echo "\x1b[31m ▄█          ▄████████    ▄▄▄▄███▄▄▄▄         ▄█  ███▄▄▄▄   \n███         ███    ███  ▄██▀▀▀███▀▀▀██▄      ███  ███▀▀▀██▄ \n███         ███    █▀   ███   ███   ███      ███▌ ███   ███ \n███        ▄███▄▄▄      ███   ███   ███      ███▌ ███   ███ \n███       ▀▀███▀▀▀      ███   ███   ███      ███▌ ███   ███ \n███         ███    █▄   ███   ███   ███      ███  ███   ███ \n███▌    ▄   ███    ███  ███   ███  ███      ███  ███   ███ \n█████▄▄██   ██████████   ▀█   ███   █▀       █▀    ▀█   █▀  \n▀                                                           "
	@echo "\x1b[33mCompilation Lem-in\x1b[0m"
	@$(CC) $(SRO) $(LIB) -o $(NAME) && echo "\x1b[32mSuccessful Lem-in Compilation\x1b[0m"

$(LIB):
	@make -C libft

%.o: %.c
	@$(CC) $(FLAGS) $< -o $@

clean:
	@make clean -C libft
	@/bin/rm -rf $(SRO)

fclean: clean
	@/bin/rm -rf $(NAME) libft/libft.a

re: fclean all
