#include "../includes/minishell.h"

int	ft_close_error(t_command_tree *tree, t_exec *exec)
{
    tree = NULL;
    exec = NULL;
	printf("free and close all\n");
	exit(0);
	return (EXIT_SUCCESS);
}