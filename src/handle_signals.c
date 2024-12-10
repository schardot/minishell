/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:16:55 by ekechedz          #+#    #+#             */
/*   Updated: 2024/12/02 21:29:21 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/redirection.h"
#include <asm-generic/signal-defs.h>

void	init_sig_hand(struct sigaction *sa_int, struct sigaction *sa_quit)
{
	sigemptyset(&sa_int->sa_mask);
	sigaddset(&sa_int->sa_mask, SIGINT);
	sa_int->sa_flags = SA_RESTART;
	sa_int->sa_handler = default_sigint_handler;
	sigaction(SIGINT, sa_int, NULL);
	sigemptyset(&sa_quit->sa_mask);
	sigaddset(&sa_quit->sa_mask, SIGQUIT);
	sa_quit->sa_flags = SA_RESTART;
	sa_quit->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, sa_quit, NULL);
}

void	switch_sig_hand(struct sigaction *sa_int, struct sigaction *sa_quit,
						bool pr_int, bool pr_quit)
{
	if (pr_int)
	{
		sa_int->sa_handler = process_running_sigint_handler;
		sigaction(SIGINT, sa_int, NULL);
	}
	else
	{
		sa_int->sa_handler = default_sigint_handler;
		sigaction(SIGINT, sa_int, NULL);
	}
	if (pr_quit)
	{
		sa_quit->sa_handler = sigquit_handler;
		sigaction(SIGQUIT, sa_quit, NULL);
	}
	else
	{
		sa_quit->sa_handler = SIG_IGN;
		sigaction(SIGQUIT, sa_quit, NULL);
	}
}

void	setup_sig_hand(struct sigaction *sa_int, struct sigaction *sa_quit)
{
	init_sig_hand(sa_int, sa_quit);
	switch_sig_hand(sa_int, sa_quit, false, false);
}
