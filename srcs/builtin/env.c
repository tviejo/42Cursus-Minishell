# include "../includes/minishell.h"

int ft_env(t_exec *exec)
{
    int i;

    i = 0;
    while (exec->env[i])
    {
        ft_putstr_fd(exec->env[i], 1);
        ft_putstr_fd("\n", 1);
        i++;
    }
    return (EXIT_SUCCESS);
}