CC = clang

FLAGS = -g
LIBFT_DIR = include/libft
LIBFT = $(LIBFT_DIR)/libft.a
NAME = minishell

SRC = src/main.c \
	src/builtins.c \
	src/parser.c \
	src/tokens.c \
	src/redirection.c \
	src/simple_command.c

READLINE_DIR = $(shell brew --prefix readline)
READLINE_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib

INCLUDES = -Iincludes -I$(LIBFT_DIR) -I$(READLINE_DIR)/include

all: $(NAME)

$(NAME): $(LIBFT)
	@echo "compile"
	$(CC) $(FLAGS) $(INCLUDES) $(LIBFT) $(SRC) $(READLINE_LIB) -o $(NAME)


$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f minishell
	make fclean -C $(LIBFT_DIR)

re: fclean all
