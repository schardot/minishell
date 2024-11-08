CC = clang

FLAGS = -g
LIBFT_DIR = include/libft
LIBFT = $(LIBFT_DIR)/libft.a
NAME = minishell

SRC = src/main.c \
	src/parser.c \
	src/executor.c \
	src/tokens.c \
	src/simple_command.c \
	src/redirection.c \
	src/pipe.c \
	src/builtins/builtin_unset.c \
	src/builtins/builtin_echo.c \
	src/builtins/builtin_cd.c \
	src/builtins/builtin_env.c \
	src/builtins/builtin_pwd.c \
	src/builtins/builtin_export.c \
	src/builtins/builtin_exit.c \
	src/builtins/builtin_utils.c \
	src/quotes.c \
	src/error.c
OBJ = $(SRC:.c=.o)

READLINE_DIR = $(shell brew --prefix readline 2>/dev/null)
READLINE_LIB = -lreadline -lhistory
INCLUDES = -Iincludes -I$(LIBFT_DIR) -I/usr/include/readline

ifdef READLINE_DIR
  READLINE_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib
  INCLUDES = -Iincludes -I$(LIBFT_DIR) -I$(READLINE_DIR)/include
else
  READLINE_LIB = -lreadline -lhistory
  INCLUDES = -Iincludes -I$(LIBFT_DIR) -I/usr/include/readline
endif


all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "compile"
	$(CC) $(FLAGS) $(INCLUDES) $(SRC) $(READLINE_LIB) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f minishell
	make fclean -C $(LIBFT_DIR)

re: fclean all
