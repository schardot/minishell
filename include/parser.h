#ifndef PARSER_H
#define PARSER_H

# define INPUT_REDIRECT  1   // Redirect input: <
# define OUTPUT_REDIRECT 2   // Redirect output: >
# define APPEND_REDIRECT 3   // Append output: >>
# define HEREDOC_REDIRECT 4  // Heredoc: <<

// Struct to manage file descriptors during redirection
typedef struct	s_redirection
{
	int	input_fd;
	int	output_fd;
}	t_redirection;

typedef struct s_tools // chatgpt suggested
{
	char **envp;	 // Environment variables
	char *cwd;		 // Current working directory
	int exit_status; // Last command exit status
	char **history;	 // Command history
	int pipefd[2];	 // Pipe file descriptors
					 // Add any additional utility functions or states as needed
} t_tools;

typedef enum
{
	COMMAND,
	ARGUMENT,
	PIPE,
	REDIRECT_OUTPUT,
	REDIRECT_INPUT,
	REDIRECT_APPEND,
	HEREDOC,
	NNEWLINE
} e_token_type;

typedef struct s_scmd // chatgpt suggested
{
	char **args;                                 // Argumentos do comando
	int (*builtin)(t_tools *, struct s_scmd *); // Ponteiro para função de built-in
	int num_redirections;                       // Número de redirecionamentos
	char *hd_file_name;                         // Nome do arquivo para heredoc, se houver
	char *redirect_token;                       // Token de redirecionamento, ex: ">"
	char *redirect_input_file;                  // Input redirection file name (<)
	char *redirect_output_file;                 // Output redirection file name (>)
	char *redirect_append_file;                 // Append redirection file name (>>)
	char *redirect_file_name;                   // Nome do arquivo de redirecionamento
	struct s_scmd *next;                        // Próximo comando
	struct s_scmd *prev;                        // Comando anterior
} t_scmd;

typedef struct s_token
{
	e_token_type type; // Type of token
	char *value;       // Actual string value of the token
	struct s_token *prev;
	struct s_token *next; // Pointer to the next token in the list
} t_token;

/* ------------------------------------------------------------------------- */
/*                           Token List Functions         		             */
/* ------------------------------------------------------------------------- */
t_token	*tokenlist_new(char *token);
void	tokenlist_addback(t_token **lst, t_token *new);
t_token	*token_list(char **tokens);
void	assign_token_type(t_token *node);

/* ------------------------------------------------------------------------- */
/*                           Simple Command Functions                        */
/* ------------------------------------------------------------------------- */
t_scmd	*scmd_new(void);
t_scmd	*simple_command(t_token *lst);
// void	handle_redirection(t_scmd *node, t_token *lst);
int		(*get_builtin_function(char *command))(t_tools *, t_scmd *);

/* ------------------------------------------------------------------------- */
/*                           Built In Functions                              */
/* ------------------------------------------------------------------------- */
int		builtincd(t_tools *t, t_scmd *node);
int		builtinecho(t_tools *t, t_scmd *node);
int		builtinpwd(t_tools *t, t_scmd *node);
int		builtinexport(t_tools *t, t_scmd *node);
int		builtinunset(t_tools *t, t_scmd *node);
int		builtinenv(t_tools *t, t_scmd *node);
int		builtinexit(t_tools *t, t_scmd *node);

/* ------------------------------------------------------------------------- */
/*                           Parser Functions                                */
/* ------------------------------------------------------------------------- */
void	parser(char *input);
void	check_exec_command(char **command);
int		is_builtin(char *token);
int		is_executable(char *cmd);


int handle_redirection(t_scmd *node);

#endif
