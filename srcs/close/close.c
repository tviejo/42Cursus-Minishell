# include "../includes/minishell.h"

int ft_close_error(t_command_tree *tree, t_exec *exec)
{
    printf("free and close all\n");
    exit(0);
    return (EXIT_SUCCESS);
}