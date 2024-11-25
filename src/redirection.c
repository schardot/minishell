/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:03:17 by ekechedz          #+#    #+#             */
/*   Updated: 2024/11/22 18:17:41 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"
#include "../include/parser.h"

int handle_input_redirection(char *file)
{
    // Check if the file exists
    if (access(file, F_OK) != 0)
    {
        perror("Error: Input file does not exist");
        return 1;
    }
    // Check if the file is readable
    if (access(file, R_OK) != 0)
    {
        perror("Error: Input file is not readable");
        return 1;
    }

    // Open the file for reading
    int new_fd = open(file, O_RDONLY);
    if (new_fd < 0)
    {
        perror("Failed to open input file");
        return 1;
    }

    // Save the current stdin file descriptor
    int old_stdin_fd = dup(STDIN_FILENO);
    if (old_stdin_fd < 0)
    {
        perror("Failed to duplicate stdin");
        close(new_fd);
        return 1;
    }

    // Close the new_fd, as stdin is now redirected
    close(new_fd);
    return 0;
}



void restore_stdout(t_scmd *node)
{
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

int handle_output_redirection(char *file)
{
	int fd;

	// Open the file in write-only mode and truncate it if it exists
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Output redirection failed");
		return -1;
	}
	close(fd);
	return 0;
}

int handle_append_redirection(char *file)
{
	int fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Append redirection failed");
		return -1;
	}
	close(fd);
	return 0;
}

int process_redirections(t_token *t, t_scmd *scmd)
{
	int result = 0;

	while (t != NULL)
	{
		if (t->type == INPUT)
		{
			scmd->redirect_fd_in = open(t->next->value, O_RDONLY);
			if (scmd->redirect_fd_in < 0)
			{
				perror("Failed to open input file");
				return 1; // Indicate an error
			}
		}
		if (t->type == OUTPUT)
		{
			scmd->redirect_fd_out = open(t->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (scmd->redirect_fd_out < 0)
			{
				perror("Failed to open output file");
				return 1; // Indicate an error
			}
		}
		if (t->type == APPEND)
		{
			scmd->redirect_fd_out = open(t->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (scmd->redirect_fd_out < 0)
			{
				perror("Failed to open append file");
				return 1; // Indicate an error
			}
		}
		// Move to the next token
		t = t->next;
	}

	return result;
}

// int execute_redirections(t_scmd *node)
// {
// 	// Handle input redirection if it exists
// 	if (node->INPUT_file)
// 	{
// 		if (handle_input_redirection(node->INPUT_file) == -1)
// 			return -1; // If input redirection fails, stop execution
// 	}

// 	// Handle output redirection if it exists
// 	if (node->OUTPUT_file)
// 	{
// 		if (handle_output_redirection(node->OUTPUT_file) == -1)
// 			return -1; // If output redirection fails, stop execution
// 	}

// 	// Handle append redirection if it exists
// 	if (node->APPEND_file)
// 	{
// 		if (handle_append_redirection(node->APPEND_file) == -1)
// 			return -1; // If append redirection fails, stop execution
// 	}

// 	// Handle heredoc redirection if it exists (implement it similarly)
// 	// if (node->R_HEREDOC_delimiter) {
// 	//    handle_heredoc(node->R_HEREDOC_delimiter);
// 	// }

// 	return 0; // Success
// }
