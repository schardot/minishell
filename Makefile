CC = clang

FLAGS = -g
LIBFT_DIR = include/libft
LIBFT = $(LIBFT_DIR)/libft.a
NAME = minishell

SRC = src/main.c \
	src/builtins.c \
	src/parser.c \
	src/tokens.c \
	src/simple_command.c \
	src/redirection.c

OBJ = $(SRC:.c=.o)

#READLINE_DIR = $(shell brew --prefix readline)
# READLINE_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib

# INCLUDES = -Iincludes -I$(LIBFT_DIR) -I$(READLINE_DIR)/include

READLINE_DIR = $(shell brew --prefix readline 2>/dev/null)
READLINE_LIB = -lreadline -lhistory
INCLUDES = -Iincludes -I$(LIBFT_DIR) -I/usr/include/readline # for linux is working in this way

#this is only because you are using MAC and for Linux again it is diff.
#This one it is not that much important
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
