#include "../includes/minishell.h"

int	ft_close_error(t_command_tree *tree, t_exec *exec)
{
    tree = NULL;
    exec = NULL;
	(void)tree;
	(void)exec;
	return (g_signal);
}