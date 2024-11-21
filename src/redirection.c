/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:03:17 by ekechedz          #+#    #+#             */
/*   Updated: 2024/11/21 14:55:17 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"
#include "../include/parser.h"

int handle_input_redirection(char *file)
{
	if (access(file, F_OK) != 0)
	{
		perror("Error: Input file does not exist");
		return 1;
	}
	if (access(file, R_OK) != 0)
	{
		perror("Error: Input file is not readable");
		return 1;
	}
	int old_stdin_fd = dup(STDIN_FILENO);
	int new_fd = open(file, O_RDONLY);
	if (new_fd < 0)
	{
		perror("Failed to open input file");
		return 1;
	}
	if (dup2(new_fd, STDIN_FILENO) < 0)
	{
		perror("Error in dup2 for stdin");
		close(new_fd);
		return 1;
	}
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

	// Redirect the standard output (STDOUT) to the file
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Failed to duplicate output file descriptor");
		close(fd); // Close the file descriptor
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
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Failed to duplicate append file descriptor");
		close(fd);
		return -1;
	}
	close(fd);
	return 0;
}

int process_redirections(t_token *t)
{
	int result = 0;

	// printf("append :%i\n", result);
	// printf("token type: %u\n", t->type);

	if (t->type == R_INPUT)
	{
		result = handle_input_redirection(t->next->value);
		if (result != 0)
			return result;
	}
	if (t->type == R_OUTPUT)
	{
		result = handle_output_redirection(t->next->value);
		if (result != 0)
			return result;
	}
	if (t->type == R_APPEND)
	{
		// printf("it is here in append\n");
		result = handle_append_redirection(t->next->value);
		if (result != 0)
			return result;
	}

	// Handle heredoc redirection
	// if (t->type->R_HEREDOC_delimiter)
	// {
	// 	result = handle_HEREDOC_redirection(t->type);
	// 	if (result != 0)
	// 		return result;
	// }
	return result;
}

int execute_redirections(t_scmd *node)
{
	// Handle input redirection if it exists
	if (node->R_INPUT_file)
	{
		if (handle_input_redirection(node->R_INPUT_file) == -1)
			return -1; // If input redirection fails, stop execution
	}

	// Handle output redirection if it exists
	if (node->R_OUTPUT_file)
	{
		if (handle_output_redirection(node->R_OUTPUT_file) == -1)
			return -1; // If output redirection fails, stop execution
	}

	// Handle append redirection if it exists
	if (node->R_APPEND_file)
	{
		if (handle_append_redirection(node->R_APPEND_file) == -1)
			return -1; // If append redirection fails, stop execution
	}

	// Handle heredoc redirection if it exists (implement it similarly)
	// if (node->R_HEREDOC_delimiter) {
	//    handle_heredoc(node->R_HEREDOC_delimiter);
	// }

	return 0; // Success
}
