#include "../include/redirection.h"
#include "../include/parser.h"

void	set_redirection(t_scmd *node, t_token *lst)
{
	if (lst->next)
	{
		if (lst->type == R_APPEND)
		{
			node->redirect_token = ">>";
			node->R_APPEND_file = lst->next->value;
			node->num_redirections++;
		}
		else if (lst->type == R_OUTPUT)
		{
			node->redirect_token = ">";
			node->R_OUTPUT_file = lst->next->value;
			node->num_redirections++;

		}
		else if (lst->type == R_INPUT)
		{
			node->redirect_token = "<";
			node->R_INPUT_file = lst->next->value;
			node->num_redirections++;
		}
	}
	else
		printf("Error");
}

// Handles input redirection: "<"
int handle_INPUT_redirection(t_scmd *node) {
	printf("Handling input redirection from file: %s\n", node->R_INPUT_file);

	node->old_stdin_fd = dup(STDIN_FILENO);
	node->new_fd = open(node->R_INPUT_file, O_RDONLY);
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
	if (dup2(node->old_stdout_fd, STDOUT_FILENO) < 0)
	{
		perror("Failed to restore STDOUT");
	}
	if (dup2(node->old_stdin_fd, STDIN_FILENO) < 0)
	{
		perror("Failed to restore STDIN");
	}
	// if (node->old_stdout_fd >= 0)
	// 	close(node->old_stdout_fd);
	// if (node->old_stdin_fd >= 0)
	// 	close(node->old_stdin_fd);
}

// Handles output redirection: ">"
int handle_OUTPUT_redirection(t_scmd *node)
{
	node->old_stdout_fd = dup(STDOUT_FILENO);
	node->new_fd = open(node->R_OUTPUT_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
int handle_APPEND_redirection(t_scmd *node)
{
	//int fd;
	node->old_stdout_fd = dup(STDOUT_FILENO);
	node->new_fd = open(node->R_APPEND_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
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
	int result = 0;

	// Handle each redirection type
	if (node->R_INPUT_file && (result = handle_INPUT_redirection(node)) != 0)
		return result;
	if (node->R_OUTPUT_file && (result = handle_OUTPUT_redirection(node)) != 0)
		return result;
	if (node->R_APPEND_file && (result = handle_APPEND_redirection(node)) != 0)
		return result;
	return result;
}

