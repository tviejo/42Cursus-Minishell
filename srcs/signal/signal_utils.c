# include "../includes/minishell.h"


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

void	signal_handler_here_doc(int sig)
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