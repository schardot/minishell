#include "../include/redirecting.h"
#include "../include/parser.h"
// Handles input redirection: "<"
int handle_input_redirection(t_scmd *node)
{
	int fd;

	fd = open(node->redirect_input_file, O_RDONLY);
	if (fd < 0)
	{
		perror("Failed to open input file");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("Error stdin");
		close (fd);
		return (-1);
	}
	close(fd);
	return (0);
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
	close(fd);
	return (0);
}

// Handles append redirection: ">>"
int handle_append_redirection(t_scmd *node)
{
	int fd;

	fd = open(node->redirect_append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("Failed to open append file");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("Error stdout");
		close(fd);
		return(-1);
	}
	close(fd);
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
