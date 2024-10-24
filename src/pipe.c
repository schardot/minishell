/*
CHAT GPT:::

Here’s a high-level overview of how to handle pipes when building your shell:

Basic Steps:
Create a pipe:

Use the pipe(int fd[2]) system call. This creates a communication channel with two ends: fd[0] for reading and fd[1] for writing.
Fork the processes:

For each command in the pipeline, create a new process using fork().
The parent process will wait for the children to finish, while the children will execute the commands.
Redirect file descriptors:

For the first command, redirect the standard output (stdout) to fd[1] using dup2(fd[1], STDOUT_FILENO).
For the second command, redirect the standard input (stdin) to fd[0] using dup2(fd[0], STDIN_FILENO).
Close unused file descriptors:

After redirection, close the file descriptors that aren’t needed.
Execute the commands:

Use execve() or similar system calls to execute the commands in the child processes.
Example:
c
Copiar código
int fd[2];
pipe(fd);  // Create a pipe

hey new change

if (fork() == 0) {  // First command
    dup2(fd[1], STDOUT_FILENO);  // Redirect stdout to the pipe
    close(fd[0]);  // Close unused read end
    close(fd[1]);  // Close write end after redirection
    execve("/bin/ls", args_ls, env);  // Execute "ls"
} else {
    if (fork() == 0) {  // Second command
        dup2(fd[0], STDIN_FILENO);  // Redirect stdin from the pipe
        close(fd[0]);  // Close read end after redirection
        close(fd[1]);  // Close unused write end
        execve("/usr/bin/wc", args_wc, env);  // Execute "wc"
    } else {
        close(fd[0]);  // Parent closes both ends
        close(fd[1]);
        wait(NULL);  // Wait for the children to finish
        wait(NULL);
    }
}
This example runs ls | wc, where the output of ls is piped into wc.

Summary:
Use pipe() to create a communication channel.
Use fork() to create child processes for each command.
Use dup2() to redirect stdout and stdin to the pipe ends.
Use execve() in the child processes to execute commands.
Close the file descriptors that aren’t needed to avoid resource leaks.
*/