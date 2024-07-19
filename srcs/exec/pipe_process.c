#include "../includes/minishell.h"

/*
int	child_process(char **cmd, t_command_tree *tree, t_exec *exec, int index)
{
	create_pipe(exec);
	exec->pid[index] = fork();
	if (exec->pid[index] == -1)
		ft_close_error(tree, exec);
	else if (exec->pid[index] == 0)
	{
		exec->fdpipe[0] = close_fd(exec->fdpipe[0], exec);
		duplicate_pipe(exec, 1);
		exec_cmd(tree, exec, cmd);
	}
	else
	{
		exec->fdpipe[1] = close_fd(exec->fdpipe[1], exec);
		duplicate_pipe(exec, 2);
		exec->fdpipe[0] = close_fd(exec->fdpipe[0], exec);
	}
	close_pipe(exec);
	return (EXIT_SUCCESS);
}
*/
