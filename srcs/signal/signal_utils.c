/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:18:34 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/07 18:17:19 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_sigint(int sig)
{
	(void)sig;
	g_signal = 128 + SIGINT;
	ft_putstr_fd("\n", 1);
}

void	signal_sigquit(int sig)
{
	(void)sig;
	g_signal = 128 + SIGINT;
	ft_putstr_fd("Quit (core dumped)\n", 2);
}

void	signal_handler(int sig)
{
	(void)sig;
	g_signal = 128 + SIGINT;
	write(STDIN_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_sigpipe(int sig)
{
	(void)sig;
	g_signal = 0;
}
