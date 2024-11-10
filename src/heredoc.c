#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/redirection.h"
int create_heredoc_temp_file(char **filename)
{
    int fd;
    *filename = malloc(strlen(".heredoc.tmp") + 1);
    if (!*filename)
        return -1;
    strcpy(*filename, ".heredoc.tmp");
    fd = open(*filename, O_WRONLY | O_CREAT, 0644);
    if (fd < 0)
    {
        perror("open");
        free(*filename);
        return -1;
    }
    close(fd);
    return 0;
}

int open_heredoc_file(char *filename)
{
    int fd;
    fd = open(filename, O_WRONLY | O_CREAT, 0644);
    if (fd < 0)
    {
        perror("open");
        return -1;
    }
    return fd;
}
int write_heredoc_input(int fd, char *delimiter)
{
    char *buf;

    while (1)
    {
        buf = readline("> ");
        if (!buf || strcmp(buf, delimiter) == 0)
        {
            if (buf)
                add_history(buf);
            free(buf);
            break;
        }

        write(fd, buf, strlen(buf));
        write(fd, "\n", 1);
        free(buf);
    }
    return 0;
}
int read_heredoc_input(char *delimiter, char *filename)
{
    int fd;
    fd = open_heredoc_file(filename);
    if (fd < 0)
        return -1;
    // struct sigaction sa;
    // sa.sa_handler = SIG_IGN;
    // sigemptyset(&sa.sa_mask);
    // sa.sa_flags = 0;
    // sigaction(SIGINT, &sa, NULL);
    if (write_heredoc_input(fd, delimiter) < 0)
    {
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}
int redirect_heredoc_input(char *filename)
{
    int fd;
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return -1;
    }
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

int handle_HEREDOC_redirection(t_scmd *node)
{
    char *delimiter;
    char *filename;
    delimiter = node->R_HEREDOC_delimiter;
    filename = NULL;
    if (create_heredoc_temp_file(&filename) < 0)
        return -1;
    if (read_heredoc_input(delimiter, filename) < 0)
    {
        unlink(filename);
        free(filename);
        return -1;
    }
    if (redirect_heredoc_input(filename) < 0)
    {
        unlink(filename);
        free(filename);
        return -1;
    }
    unlink(filename);
    free(filename);
    return 0;
}