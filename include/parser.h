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
	int		exit_status;
	int		pipefd[2];
	char	cwd[PATH_MAX];
	int		exit;
	int		totalp;
} t_tools;

typedef enum
{
	NO_TYPE,
	COMMAND,
	ARGUMENT,
	PIPE,
	OUTPUT,
	INPUT,
	APPEND,
	R_HEREDOC,
	O_FILE,
	I_FILE,
	A_FILE,
	H_DEL
} e_token_type;

typedef struct s_token
{
	e_token_type	type;
	char			*value;
	bool			sq;
	bool			dq;
	struct s_token	*prev;
	struct s_token	*next;
} t_token;

typedef struct s_parser
{
	bool			sq;
	bool			dq;
	char            *arg;
	char            *expanded;
	char		    *input;
	t_token		    *tk_lst;
} t_parser;

typedef struct s_scmd
{
	char			**args;
	int				argsc;
	int 			(*builtin)(t_tools *, struct s_scmd *);
	char			*exec_path;
	int				num_redirections;
	char			*hd_file_name;
	char			*redirect_token;
	char            *R_HEREDOC_delimiter;
	char			*redirect_file_name;
	int				old_stdin_fd;
	int				old_stdout_fd;
	int				new_fd;
	int				pipecount;
	int				redirect_fd_in;
	int				redirect_fd_out;
	int				pipetotal;
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
t_token		*tokenlist_new(char *token, t_tools *t, t_parser *p);
void		tokenlist_addback(t_token **lst, t_token *new);
void		assign_token_type(t_token *node, t_tools *t);
void		assign_token_files(t_token *tk);

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
int		check_quote(int i, t_parser *p, t_tools *t);
char	*trim_quotes(char *arg);
int		builtinpwd(t_tools *t, t_scmd *node);
int		builtinexport(t_tools *t, t_scmd *node);
int		builtinunset(t_tools *t, t_scmd *node);
void	export_empty(void);
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
int		handle_expansions(t_parser *p, int i, t_tools *t);
int		create_quoted_arg(t_parser *p, int i, char q, t_tools *t);

/* ------------------------------------------------------------------------- */
/*                           Cleanup Functions                               */
/* ------------------------------------------------------------------------- */
void    free_structs(t_scmd *s, t_token *lst, t_parser *p);
void    free_parser(t_parser *p);
void	free_token(t_token *lst);
void	free_scmd(t_scmd *s);

/* ------------------------------------------------------------------------- */
/*                            Syntax Functions                               */
/* ------------------------------------------------------------------------- */
int syntax_check(t_token *lst, t_tools *t);




int syntax_check(t_token *lst, t_tools *t);
void	process_running_sigint_handler(int signum);
char	**ft_append_to_arr(char **arr, char *str, int len);
int process_redirections(t_token *t, t_scmd *scmd);
char *append_char(char *arg, char c);
t_token	*split_arguments(t_parser *p, t_tools *t);
t_parser *init_parser(char *input);
char *check_env(t_parser *p, char *arg);
int execute_redirections(t_scmd *node);
int initial_quote_check(char *arg);
t_parser *append_token(t_parser *p, t_tools *t);
char *ft_getenv(char *env, t_tools *t);
char	*expand_the_argument(char *arg, int *i, int start, t_tools *t);
void symbol_check(int *i, t_parser *p, t_tools *t);
char	*create_full_path(char **paths, char *cmd);
void	handle_type(t_token *t, t_scmd *s, t_scmd *next_command);
int	after_fork(t_tools *t, t_scmd *scmd, t_exec *e);

#endif
