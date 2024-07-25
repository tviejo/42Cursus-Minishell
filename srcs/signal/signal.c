/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:15 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/25 11:52:17 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

int g_signal;

void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        ft_putstr_fd("\n", 1);
        g_signal = 130;
    }
}

void signal_handler_here_doc(int sig)
{
    if (sig == SIGINT)
    {
        ft_putstr_fd("\n", 1);
        g_signal = 130;
    }
    if (sig == SIGQUIT)
    {
        ft_putstr_fd("Quit: 3\n", 1);
        g_signal = 131;
    }
}

void signal_handler_process(int sig)
{
    if (sig == SIGINT)
    {
        ft_putstr_fd("\n", 1);
        g_signal = 130;
    }
}