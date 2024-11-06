#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/redirection.h"

t_scmd *simple_command(t_token *t)
{
    t_scmd *s;

    s = scmd_new();
    while (t)
    {
        if (t->type == ARGUMENT || t->type == COMMAND)
            handle_argument(s, t);
        else if (t->type == PIPE)
            handle_pipe(s, t);
        else
            handle_redirection(s, &t);
        t = t->next;
    }
    return (s);
}

// Handle arguments and built-in detection
void handle_argument(t_scmd *s, t_token *t)
{
    s->args = ft_arrcat(s->args, t->value, ft_str2dlen(s->args));
    s->argsc++;
    if (t->type == COMMAND && is_builtin(s->args[0]))
        s->builtin = get_builtin_function(s->args[0]);
}

// Set up next command in pipeline if PIPE is encountered
void handle_pipe(t_scmd *s, t_token *t)
{
    t_scmd *next_command = simple_command(t->next);

    s->next = next_command;
    if (next_command)
        t->next = NULL;
}

// Set redirection for the command
void handle_redirection(t_scmd *s, t_token **t)
{
    set_redirection(s, *t);
    *t = (*t)->next;
}