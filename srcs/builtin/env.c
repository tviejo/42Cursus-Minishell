# include "../includes/minishell.h"

int ft_env(t_data *exec, t_command_tree *tree)
{
    int i;

    i = 0;
    if (tree->argument[1] != NULL)
    {
        ft_putstr_fd("env: '", 1);
        ft_putstr_fd(tree->argument[1], 1);
        ft_putstr_fd("': No such file or directory\n", 1);
        return (EXIT_FAILURE);
    }
    while (exec->env[i])
    {
        ft_putstr_fd(exec->env[i], 1);
        ft_putstr_fd("\n", 1);
        i++;
    }
    return (EXIT_SUCCESS);
}