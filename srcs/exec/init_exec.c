#include "../includes/minishell.h"

int	calloc_pid(t_exec *exec, t_command_tree *tree)
{
	int i;

	i = 0;
	exec->pid = (pid_t *)ft_calloc(sizeof(pid_t) , tree->nb_command);
	if (exec->pid == NULL)
        ft_close_error(tree, exec);
	while (i < tree->nb_command)
	{
		exec->pid[i] = -1;
		i++;
	}
	return (EXIT_SUCCESS);
}