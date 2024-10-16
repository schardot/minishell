CC = clang

FLAGS = -Wall -Wextra -Werror
LIBFT_DIR = include/libft
LIBFT = $(LIBFT_DIR)/libft.a
NAME = minishell

SRC = src/main.c \
	include/libft/get_next_line/get_next_line.c \
	include/libft/get_next_line/get_next_line_utils.c

OBJ = $(SRC:.c=.o)

READLINE_DIR = $(shell brew --prefix readline)
READLINE_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib

INCLUDES =-Iincludes -I$(LIBFT_DIR) -I$(READLINE_DIR)/include

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(FLAGS) $(LIBFT) $(OBJ) $(READLINE_LIB) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f minishell
	make fclean -C $(LIBFT_DIR)

re: fclean all
