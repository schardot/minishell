/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:08:43 by ekechedz          #+#    #+#             */
/*   Updated: 2024/12/04 14:08:45 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <sys/stat.h>
# include <unistd.h>

typedef enum s_token_type
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
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	bool			sq;
	bool			dq;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_parser
{
	bool			sq;
	bool			dq;
	char			q;
	char			*arg;
	char			*expanded;
	char			*input;
	t_token			*tk_lst;
}	t_parser;

typedef struct s_tools	t_tools;

typedef struct s_scmd
{
	char			**args;
	int				argsc;
	int				(*builtin)(t_tools *, struct s_scmd *);
	char			*exec_path;
	int				num_redirections;
	char			*hd_file_name;
	char			*redirect_token;
	char			*r_heredoc_delimiter;
	char			*redirect_file_name;
	int				old_stdin_fd;
	int				old_stdout_fd;
	int				new_fd;
	int				pipecount;
	int				redirect_fd_in;
	int				redirect_fd_out;
	int				skip_exec;
	int				pipetotal;
	int				heredoc_failed;
	struct s_scmd	*next;
	struct s_scmd	*prev;
}	t_scmd;

typedef struct s_exec {
	int		prev_fd;
	int		has_next;
	pid_t	pid;
	int		n;
	int		status;
	int		pids[250];
}	t_exec;

typedef struct s_tools
{
	char		**envp;
	int			stdin_backup;
	int			stdout_backup;
	int			exit_status;
	int			pipefd[2];
	char		cwd[PATH_MAX];
	int			exit;
	int			totalp;
	t_scmd		*scmd;
	t_parser	*parser;
	t_token		*tk;
	t_exec		*e;
}	t_tools;

/* ------------------------------------------------------------------------- */
/*                           Token List Functions         		             */
/* ------------------------------------------------------------------------- */
t_token		*tokenlist_new(char *token, t_tools *t, t_parser *p);
void		tokenlist_addback(t_token **lst, t_token *new);
void		assign_token_type(t_token *node, t_tools *t);
void		assign_token_files(t_token *tk);
t_parser	*append_token(t_parser *p, t_tools *t);
void		handle_type(t_tools *t, t_token *tk, t_scmd *s, \
t_scmd *next_command);

/* ------------------------------------------------------------------------- */
/*                                  Init                                     */
/* ------------------------------------------------------------------------- */
void		init_scmd_args(t_scmd *scmd);
void		init_scmd_redirections(t_scmd *scmd);
void		init_scmd_fds(t_scmd *scmd);
void		init_scmd_pipes(t_scmd *scmd);
void		init_scmd_next_prev(t_scmd *scmd);
t_parser	*init_parser(char *input);

/* ------------------------------------------------------------------------- */
/*                           Simple Command Functions                        */
/* ------------------------------------------------------------------------- */
t_scmd		*scmd_new(void);
t_scmd		*simple_command(t_tools *t, t_token *lst);
int			(*get_builtin_function(char *command))(t_tools *, t_scmd *);

/* ------------------------------------------------------------------------- */
/*                           Built In Functions                              */
/* ------------------------------------------------------------------------- */
int			builtincd(t_tools *t, t_scmd *node);
int			builtinecho(t_tools *t, t_scmd *node);
int			check_quote(int i, t_parser *p, t_tools *t);
char		*trim_quotes(char *arg);
int			builtinpwd(t_tools *t, t_scmd *node);
int			builtinexport(t_tools *t, t_scmd *node);
char		**sort_arr(char **arr);
void		replace_env_var(char *full, int len, t_tools *t);
int			check_exp_args(char *arg, t_scmd *scmd, t_tools *t);
int			export_var(t_scmd *scmd, char *full, char **spl, t_tools *t);
int			process_export_var(char *arg, t_tools *t);
int			builtinunset(t_tools *t, t_scmd *node);
int			builtinenv(t_tools *t, t_scmd *node);
int			builtinexit(t_tools *t, t_scmd *node);
int			builtinhistory(t_tools *t, t_scmd *node);

/* ------------------------------------------------------------------------- */
/*                           Parser Functions                                */
/* ------------------------------------------------------------------------- */
int			parser(char *input, t_tools *t);
int			check_exec_command(t_tools *t, t_scmd *scmd);
int			is_builtin(char *token);
char		*is_executable(char *cmd, t_tools *t);
int			handle_expansions(t_parser *p, int i, t_tools *t);
void		symbol_check(int *i, t_parser *p, t_tools *t);
char		*append_char(char *arg, char c);
t_token		*split_arguments(t_parser *p, t_tools *t);
int			initial_quote_check(char *arg);
char		*ft_getenv(char *env, t_tools *t);
char		*expand_the_argument(char *arg, int *i, int start, t_tools *t);
void		symbol_check(int *i, t_parser *p, t_tools *t);
char		*create_full_path(char **paths, char *cmd);

/* ------------------------------------------------------------------------- */
/*                           Cleanup Functions                               */
/* ------------------------------------------------------------------------- */
void		free_structs(t_tools *t);
void		free_parser(t_parser *p);
void		free_token(t_token *lst);
void		free_scmd(t_scmd *s);
int			free_tools(t_tools *t);

/* ------------------------------------------------------------------------- */
/*                            Syntax Functions                               */
/* ------------------------------------------------------------------------- */
int			syntax_check(t_token *lst, t_tools *t);

/* ------------------------------------------------------------------------- */
/*                                Execution                                  */
/* ------------------------------------------------------------------------- */

t_exec		*init_t_exec(void);
int			old_stdin_fd(t_scmd *scmd);
void		unlink_heredoc(t_scmd *scmd);
void		handle_one(t_scmd *scmd);
int			after_fork(t_tools *t, t_scmd *scmd, t_exec *e);
void		handle_redirection(t_scmd *scmd);

/* ------------------------------------------------------------------------- */
/*                                   Signals                                 */
/* ------------------------------------------------------------------------- */

void		sigquit_handler(int signum);
void		process_running_sigint_handler(int signum);
void		default_sigint_handler(int signum);

/* ------------------------------------------------------------------------- */
/*                                   Heredoc                                 */
/* ------------------------------------------------------------------------- */

int			create_heredoc_temp_file(char **filename);
void		heredoc_sigint_handler(int sig);
int			write_heredoc_input(int fd, const char *delimiter);
int			handle_heredoc_child(const char *delimiter, char *filename);
int			wait_for_heredoc_process(pid_t pid, char *filename);

#endif
