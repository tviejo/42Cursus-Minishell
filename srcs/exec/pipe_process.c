#include "../includes/minishell.h"

int	child_process(char **cmd, t_command_tree *tree, t_exec *exec)
{
	int index;

	create_pipe(exec, tree);
	index = create_fork(tree, exec);
	if (exec->pid[index] == 0)
	{
		exec->fdpipe[0] = close_fd(exec->fdpipe[0], tree, exec);
		duplicate_pipe(tree, exec, 1);
		exec_cmd(tree, exec, cmd);
	}
	else
	{
		exec->fdpipe[1] = close_fd(exec->fdpipe[1], tree, exec);
		duplicate_pipe(tree, exec, 2);
		exec->fdpipe[0] = close_fd(exec->fdpipe[0], tree, exec);
	}
	close_pipe(exec);
	return (EXIT_SUCCESS);
}

int	last_child_process(char **cmd, t_command_tree *tree, t_exec *exec)
{
	int index;

	index = create_fork(tree, exec);
	if (exec->pid[index] == 0)
	{
		exec_cmd(tree, exec, cmd);
	}
	return (EXIT_SUCCESS);
}