#include "../includes/minishell.h"

int		g_signal;

bool	wait_one_process(t_data *exec)
{
	int	status;

	status = 0;
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		exec->error_code = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		exec->error_code = 128 + WTERMSIG(status);
	}
	return (true);
}

void	wait_all_process(t_data *exec)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
		{
			exec->error_code = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			exec->error_code = 128 + WTERMSIG(status);
		}
	}
}
