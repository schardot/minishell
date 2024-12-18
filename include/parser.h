#ifndef PARSER_H
#define PARSER_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

typedef struct s_tools
{
	char	**envp;
	int		stdin_backup; //elmira are you using this
	int		stdout_backup; //this also
	int     exit_status;
	int     pipefd[2];	 //elmira do you use this
} t_tools;

typedef struct s_parser
{
	bool	dq;
	bool	sq;
	bool	append;
	char	**tokens;
	char	*input;
} t_parser;

typedef enum
{
	COMMAND,
	ARGUMENT,
	PIPE,
	R_OUTPUT,
	R_INPUT,
	R_APPEND,
	R_HEREDOC
} e_token_type;

typedef struct s_token
{
	e_token_type	type;
	char			*value;
    int             redirect_count;
	int				pipe_count;
	bool			sq;
	bool			dq;
	struct s_token	*prev;
	struct s_token	*next;
} t_token;

typedef struct s_scmd
{
	char			**args;
	int				argsc;
	int 			(*builtin)(t_tools *, struct s_scmd *);
	char			*exec_path;
	int				num_redirections;
	char			*hd_file_name;
	char			*redirect_token;
	char			*R_INPUT_file;
	char			*R_OUTPUT_file;
	char			*R_APPEND_file;
    char            *R_HEREDOC_delimiter;
	char			*redirect_file_name;
	int				old_stdin_fd;
	int				old_stdout_fd;
	int				new_fd;
	int				pipecount;
	struct s_scmd	*next;
	struct s_scmd	*prev;
} t_scmd;

typedef struct s_exec {
	int	prev_fd;
	int	has_next;
	pid_t	pid;
	int n;
	int	status;
	int 	pids[250];
} t_exec;

/* ------------------------------------------------------------------------- */
/*                           Token List Functions         		             */
/* ------------------------------------------------------------------------- */
t_token *tokenlist_new(char *token, t_tools *t);
void	tokenlist_addback(t_token **lst, t_token *new);
t_token *token_list(char **tokens, t_tools *t);
void assign_token_type(t_token *node, t_tools *t);

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
char	*trim_quotes(char *arg, bool trim);
int		builtinpwd(t_tools *t, t_scmd *node);
int		builtinexport(t_tools *t, t_scmd *node);
int		builtinunset(t_tools *t, t_scmd *node);
int		check_unset_args(t_scmd *scmd, t_tools *t);
void    export_empty(void);
int     create_new_envp(t_scmd *scmd, t_tools *t);
int		builtinenv(t_tools *t, t_scmd *node);
int		builtinexit(t_tools *t, t_scmd *node);
int		builtinhistory(t_tools *t, t_scmd *node);

/* ------------------------------------------------------------------------- */
/*                           Parser Functions                                */
/* ------------------------------------------------------------------------- */
int		parser(char *input, t_tools *t);
int		check_exec_command(t_tools *t, t_scmd *scmd);
int		is_builtin(char *token);
char	*is_executable(char *cmd, t_tools *t);



void	process_running_sigint_handler(int signum);
//int handle_redirection(t_scmd *node);
char	**ft_append_to_arr(char **arr, char *str, int len);

char *append_char(char *arg, char c);
char **split_arguments(t_parser *p, t_tools *t);
t_parser *init_parser(char *input);
int	check_quote(char c, char **arg, t_parser *p);
char *check_env(t_parser *p, char *arg);

int initial_quote_check(char *arg);
t_parser *append_token(char **arg, t_parser *p, t_tools *t);
char *ft_getenv(char *env, t_tools *t);
char	*expand_the_argument(char *arg, int *i, int start, t_tools *t);
void symbol_check(char **arg, int *i, t_parser *p, t_tools *t);
char	*create_full_path(char **paths, char *cmd);
void	handle_type(t_token *t, t_scmd *s, t_scmd *next_command);
int	after_fork(t_tools *t, t_scmd *scmd, t_exec *e);

#endif
