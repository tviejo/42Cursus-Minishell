# include "../includes/minishell.h"

void	*ft_calloc_pid(t_command_tree *tree, t_exec *exec)
{
	exec->pid = ft_calloc(tree->nb_command, sizeof(pid_t));
	if (exec->pid == NULL)
		ft_close_error(tree, exec, 2);
	ft_memset(exec->pid, -10, tree->nb_command);
	return (exec->pid);
}

int	create_pipe(t_exec *exec, t_cmdtree *tree)
{
    if (pipe(exec->fdpipe) == -1)
    {
        ft_close_error(tree, exec, 2);
    }
    return (EXIT_SUCCESS);
}

int	close_pipe(t_exec *exec)
{
	if (exec->fdpipe[0] > 2)
		close(exec->fdpipe[0]);
	if (exec->fdpipe[1] > 2)
		close(exec->fdpipe[1]);
	return (EXIT_SUCCESS);
}

int	duplicate_pipe(t_command_tree *tree, t_exec *exec, int mode)
{
	if (mode == 1)
	{
		if (dup2(exec->fdpipe[1], STDOUT_FILENO) == -1)
			ft_close_error(tree, exec, 2);
		close(exec->fdpipe[1]);
		exec->fdpipe[1] = -1;
	}
	else
	{
		if (dup2(exec->fdpipe[0], STDIN_FILENO) == -1)
			ft_close_error(tree, exec, 2);
		close(exec->fdpipe[0]);
		exec->fdpipe[0] = -1;
	}
	return (EXIT_SUCCESS);
}

int	close_fd(int fd, t_command_tree *tree, t_exec *exec)
{
    if (fd >= 0 && fd <= 1024)
    {
        if (close(fd) == -1)
        {
            ft_close_error(tree, exec);
        }
    }
    return (-1);
}