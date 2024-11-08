#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/redirection.h"
#include <asm-generic/signal-defs.h>

void	default_sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();

	}
}

// Signal handler when a process is running (e.g., for background jobs)
void	process_running_sigint_handler(int signum)
{
	(void)signum;
	ft_putendl_fd("", STDOUT_FILENO);
}

// Signal handler for SIGQUIT
void	sigquit_handler(int signum)
{
	ft_putendl_fd("Quit", STDOUT_FILENO);
	(void)signum;
}

void	init_signal_handlers(struct sigaction *sa_int, struct sigaction *sa_quit)
{
	// Handle SIGINT
	sigemptyset(&sa_int->sa_mask);
	sigaddset(&sa_int->sa_mask, SIGINT);
	sa_int->sa_flags = SA_RESTART;
	sa_int->sa_handler = default_sigint_handler;
	sigaction(SIGINT, sa_int, NULL);

	// Handle SIGQUIT (ignoring by default)
	sigemptyset(&sa_quit->sa_mask);
	sigaddset(&sa_quit->sa_mask, SIGQUIT);
	sa_quit->sa_flags = SA_RESTART;
	sa_quit->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, sa_quit, NULL);
}

void	switch_signal_handlers(struct sigaction *sa_int, struct sigaction *sa_quit, bool pr)
{
	if (pr)
	{
		sa_int->sa_handler = process_running_sigint_handler;
		sigaction(SIGINT, sa_int, NULL);
		sa_quit->sa_handler = sigquit_handler;
		sigaction(SIGQUIT, sa_quit, NULL);
	}
	else
	{
		sa_int->sa_handler = default_sigint_handler;
		sigaction(SIGINT, sa_int, NULL);
		sa_quit->sa_handler = SIG_IGN;
		sigaction(SIGQUIT, sa_quit, NULL);
	}
}

// Function to setup signal handling
void	setup_signal_handling(struct sigaction *sa_int, struct sigaction *sa_quit)
{
	init_signal_handlers(sa_int, sa_quit);
	switch_signal_handlers(sa_int, sa_quit, false);
}
