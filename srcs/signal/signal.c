/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:15 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/07 17:49:26 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_signal;

int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

void	signal_init(void)
{
	g_signal = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	signal_handler_process(void)
{
	signal(SIGINT, signal_sigint);
	signal(SIGQUIT, signal_sigquit);
	signal(SIGPIPE, signal_sigpipe);
}

void	signal_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal = 128 + SIGINT;
	rl_replace_line("", 0);
	rl_redisplay();
	rl_done = 1;
}

void	signal_here_doc(void)
{
	g_signal = 0;
	rl_event_hook = sig_event;
	signal(SIGINT, signal_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
