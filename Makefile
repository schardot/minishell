CC = clang

FLAGS = -Wall -Wextra -Werror
LIBFT_DIR = include/libft
LIBFT = $(LIBFT_DIR)/libft.a

all = minishell

SRC = src/main.c \
	include/libft/get_next_line/get_next_line.c \
	include/libft/get_next_line/get_next_line_utils.c

OBJ = $(SRC:.c=.o)

minishell: $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) -o minishell $(OBJ) $(LIBFT)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f minishell

re: fclean all
