#include "../include/redirection.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>  // For perror()


// Handles input redirection: "<"
int handle_input_redirection(t_scmd *node)
{
	int fd;

	if (node->redirect_token && ft_strcmp(node->redirect_token, "<") == 0)
	{
		fd = open(node->redirect_input_file, O_RDONLY);
		if (fd == -1)
		{
			perror("Failed to open input file");
			return (-1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

// Handles output redirection: ">"
int handle_output_redirection(t_scmd *node)
{
	int fd;

	if (node->redirect_token && ft_strcmp(node->redirect_token, ">") == 0)
	{
		fd = open(node->redirect_output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("Failed to open output file");
			return (-1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

// Handles append redirection: ">>"
int handle_append_redirection(t_scmd *node)
{
	int fd;

	if (node->redirect_token && ft_strcmp(node->redirect_token, ">>") == 0)
	{
		fd = open(node->redirect_append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("Failed to open append file");
			return (-1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}
