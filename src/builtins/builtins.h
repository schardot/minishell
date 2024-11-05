#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../include/minishell.h"
# include "../../include/parser.h"
# include "../../include/redirection.h"
#include "../../include/libft/libft.h"
# include <stdlib.h>

int     builtinunset(t_tools *t, t_scmd *scmd);
int     check_unset_args(t_scmd *scmd);
void    export_empty(void);
int     create_new_envp(t_scmd *scmd, t_tools *t);

#endif