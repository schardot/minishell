#include "../include/redirection.h"
#include "../include/parser.h"

void	set_redirection(t_scmd *node, t_token *lst)
{
	if (lst->type == REDIRECT_APPEND)
	{
		node->redirect_token = ">>";
		node->redirect_append_file = lst->next->value;
		node->num_redirections++;
	}
	else if (lst->type == REDIRECT_OUTPUT)
	{
		node->redirect_token = ">";
		node->redirect_output_file = lst->next->value;
		node->num_redirections++;

	}
	else if (lst->type == REDIRECT_INPUT)
	{
		node->redirect_token = "<";
		node->redirect_input_file = lst->next->value;
		node->num_redirections++;
	}
}

// Handles input redirection: "<"
int handle_input_redirection(t_scmd *node) {
	printf("Handling input redirection from file: %s\n", node->redirect_input_file);
	int fd = open(node->redirect_input_file, O_RDONLY);
	if (fd < 0)
	{
		perror("Failed to open input file");
		return -1;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("Error in dup2 for stdin");
		close(fd);
		return -1;
	}
	close(fd);
	return 0;
}



// Handles output redirection: ">"
int handle_output_redirection(t_scmd *node)
{
	int fd;

	fd = open(node->redirect_output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Failed to open output file");
		return (-1);
	}

	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("Error redirecting stdout");
		close(fd);
		return (-1);
	}
	printf("%s", node->args[1]);
	close(fd);
	return (0);
}

// Handles append redirection: ">>"
int handle_append_redirection(t_scmd *node)
{
	//int fd;

	node->old_fd = dup(STDOUT_FILENO);
	node->new_fd = open(node->redirect_append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (node->new_fd < 0)
	{
		perror("Failed to open append file");
		return (-1);
	}
	if (dup2(node->new_fd, STDOUT_FILENO) < 0)
	{
		perror("Error stdout");
		close(node->new_fd);
		return(-1);
	}
	close(node->new_fd);
	return (0);
}

int handle_redirection(t_scmd *node)
{
	if (ft_strncmp(node->redirect_token, ">", 2) == 0)
		return (handle_output_redirection(node));
	else if (ft_strncmp(node->redirect_token, ">>", 3) == 0)
		return (handle_append_redirection(node));
	else if (ft_strncmp(node->redirect_token, "<", 2) == 0)
		return(handle_input_redirection(node));

	return (0);
}

