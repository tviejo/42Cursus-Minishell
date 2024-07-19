# include "../includes/minishell.h"

int ft_free_pid(t_exec *exec)
{
    free(exec->pid);
    return (EXIT_SUCCESS);
}