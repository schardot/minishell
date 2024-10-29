#ifndef PARSER_H
#define PARSER_H

typedef struct s_tools // chatgpt suggested
{
	char **envp;	 // Environment variables
	int	stdin_backup;
	int	stdout_backup;
	//char *cwd;		 // Current working directory
	//int exit_status; // Last command exit status
	//char **history;	 // Command history
	//int pipefd[2];	 // Pipe file descriptors
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
	HEREDOC
} e_token_type;

typedef struct s_token
{
	e_token_type type; // Type of token
	char *value;       // Actual string value of the token
	struct s_token *prev;
	struct s_token *next; // Pointer to the next token in the list
} t_token;

typedef struct s_scmd
{
	char			**args;
	int 			(*builtin)(t_tools *, struct s_scmd *);
	char			*exec_path;
	char			quote_token;
	int				num_redirections;
	char			*hd_file_name;
	char			*redirect_token;
	char			*redirect_input_file;
	char			*redirect_output_file;
	char			*redirect_append_file;
	char			*redirect_file_name;
	struct s_scmd	*next;
	struct s_scmd	*prev;
} t_scmd;



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
int		(*get_builtin_function(char *command))(t_tools *, t_scmd *);

/* ------------------------------------------------------------------------- */
/*                           Built In Functions                              */
/* ------------------------------------------------------------------------- */
int		builtincd(t_tools *t, t_scmd *node);
int		builtinecho(t_tools *t, t_scmd *node);
int		check_quotes(char *arg);
char	*trim_quotes(char *arg, t_scmd *scmd);
int		builtinpwd(t_tools *t, t_scmd *node);
int		builtinexport(t_tools *t, t_scmd *node);
int		builtinunset(t_tools *t, t_scmd *node);
int		builtinenv(t_tools *t, t_scmd *node);
int		builtinexit(t_tools *t, t_scmd *node);

/* ------------------------------------------------------------------------- */
/*                           Parser Functions                                */
/* ------------------------------------------------------------------------- */
void	parser(char *input, t_tools *t);
int		check_exec_command(t_tools *t, t_scmd *scmd);
int		is_builtin(char *token);
char	*is_executable(char *cmd);
char	*format_arg(t_scmd *scmd, char *arg);




int handle_redirection(t_scmd *node);
char	**ft_append_to_arr(char **arr, char *str, int len);

#endif
