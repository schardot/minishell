#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/redirection.h"

int	builtinecho(t_tools *t, t_scmd *scmd)
{
	int		flag;
	char	*output;
	char	*arg;
	char	*temp;
	int		i;

	handle_redirection(scmd);
	if (!scmd->args[1])
		printf("\n");
	if (!ft_strncmp(scmd->args[1], "-n", ft_strlen(scmd->args[1])))
		flag = 1;
	else
		flag = 0;
	i = flag + 1;
	arg = ft_strdup("");
	while (scmd->args[i])
	{
		output = format_arg(scmd, scmd->args[i]);
		if (!output)
		{
			// free(arg);
			return (-1);
		}
		temp = ft_strjoin(arg, output);
		// free (arg);
		arg = temp;
		// i made it with if to can check if there is one more argv. If there is no more to not put extra space.
		if (scmd->args[i + 1])
		{
			temp = ft_strjoin(arg, " ");
			// free(arg);
			arg = temp;
		}
		i++;
	}
	ft_putstr_fd(arg, STDOUT_FILENO);
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	restore_stdout(scmd);
	// printf("%s", arg);
	//  if (flag == 0)// -- this one is not correct because in the case of echo the flag will always be 0
	//  	printf("\n");
	// free(arg);
	return (0);
}