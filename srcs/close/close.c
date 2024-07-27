#include "minishell.h"

int	ft_close_error(t_command_tree *tree, t_data *exec)
{
	(void)tree;
	ft_free_pid(exec);
	close_std_fd(exec);
	free_cmdtree(exec);
	free_env(exec);
	free_parsing(exec);
	return (EXIT_FAILURE);
}