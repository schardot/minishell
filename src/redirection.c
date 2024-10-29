#include "../include/redirection.h"
#include "../include/parser.h"

void	set_redirection(t_scmd *node, t_token *lst)
{
	if (lst->next)
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
	else
		printf("Error");
}

// Handles input redirection: "<"
int handle_input_redirection(t_scmd *node) {
	printf("Handling input redirection from file: %s\n", node->redirect_input_file);

	node->old_fd = dup(STDIN_FILENO);
	node->new_fd = open(node->redirect_input_file, O_RDONLY);
	if (node->new_fd < 0)
	{
		perror("Failed to open input file");
		return -1;
	}
	if (dup2(node->new_fd, STDIN_FILENO) < 0)
	{
		perror("Error in dup2 for stdin");
		close(node->new_fd);
		return -1;
	}
	close(node->new_fd);
	return 0;
}

void restore_stdout(t_scmd *node)
{
	// Restore the original STDOUT from old_fd
	if (dup2(node->old_fd, STDOUT_FILENO) < 0)
	{
		perror("Failed to restore STDOUT");
	}
	if (dup2(node->old_fd, STDIN_FILENO) < 0)
	{
		perror("Failed to restore STDIN");
	}
	close(node->old_fd);
}

// Handles output redirection: ">"
int handle_output_redirection(t_scmd *node)
{
	node->old_fd = dup(STDOUT_FILENO);
	node->new_fd = open(node->redirect_output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (node->new_fd < 0)
	{
		perror("Failed to open output file");
		return (-1);
	}

	if (dup2(node->new_fd, STDOUT_FILENO) < 0)
	{
		perror("Error redirecting stdout");
		close(node->new_fd);
		return (-1);
	}
	close(node->new_fd);
	return (0);
}

// Handles append redirection: ">>"
int handle_append_redirection(t_scmd *node)
{
	//int fd;
	node->old_fd = dup(STDOUT_FILENO);
	node->new_fd = open(node->redirect_append_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (node->new_fd < 0)
	{
		perror("Failed to open append file");
		return (-1);
	}
	if (dup2(node->new_fd, STDOUT_FILENO) < 0)
	{
		perror("Error stdout");
		close(node->new_fd);
		//close(node->old_fd);
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

