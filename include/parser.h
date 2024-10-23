#ifndef PARSER_H
#define PARSER_H

typedef struct s_scmd // chatgpt suggested
{
    char **str;                                 // Argumentos do comando
    int (*builtin)(t_tools *, struct s_scmd *); // Ponteiro para função de built-in
    int num_redirections;                       // Número de redirecionamentos
    char *hd_file_name;                         // Nome do arquivo para heredoc, se houver
    char *redirect_token;                       // Token de redirecionamento, ex: ">"
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

typedef enum
{
    COMMAND,
    ARGUMENT,
    PIPE,
    REDIRECT_OUTPUT,
    REDIRECT_INPUT,
    REDIRECT_APPEND,
    HEREDOC,
    NEWLINE,
    UNKNOWN
} e_token_type;

typedef struct s_tools // chatgpt suggested
{
    char **envp;     // Environment variables
    char *cwd;       // Current working directory
    int exit_status; // Last command exit status
    char **history;  // Command history
    int pipefd[2];   // Pipe file descriptors
                     // Add any additional utility functions or states as needed
} t_tools;

t_token *tklist_new(char *token);
void tklist_addback(t_token **lst, t_token *new);
void parser(char *input);
void check_exec_command(char **command);
int is_builtin(char *token);
int is_executable(char *cmd);
int is_executable(char *cmd);
void execute_builtin(char **cmd, int len);
void cd(const char *path);
void pwd(void);

#endif