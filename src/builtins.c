#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/redirection.h"


int	builtinexport(t_tools *t, t_scmd *node)
{
	/* - - - - - - - - - - - - - - - - - - - - - CHAT GPT - - - - - - - - - - - - - - - - - - - - - - - - - - -
	**export** (with no options):
   - Sets environment variables.
   - Example: `export VAR=value` sets `VAR` in the environment.*/
	(void)node;
	(void)t;
	return (0);
}
