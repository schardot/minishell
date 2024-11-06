#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/redirection.h"

int builtinexit(t_tools *t, t_scmd *node)
{
    int exit_status = 0;
    //int return_value;

    //return_value = 1;

    if (node && node->args && node->args[1])
    {                                     
        exit_status = atoi(node->args[1]); 
        if (exit_status == 0 && node->args[1][0] != '0')
        {
            printf("minishell: exit: %s: numeric argument required\n", node->args[1]);
            exit_status = 2; 
        }
    }

    // // Optional: Print "exit" if it’s not a child process
    // if (!t->is_child)
    // {
    //     printf("exit\n");
    // }
    // cleanup_tools(t);   // You might implement this to free memory and close descriptors
    // cleanup_node(node); // Likewise, to free resources specific to the command node
    exit(exit_status);
    return -1;
}
