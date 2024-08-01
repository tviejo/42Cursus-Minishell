/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:15 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/31 22:53:29 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_signal;

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
}

void	signal_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal = 128 + SIGINT;
}

void	signal_here_doc(void)
{
	g_signal = 0;
	signal(SIGINT, signal_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
