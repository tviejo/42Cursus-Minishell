# include "../includes/minishell.h"

int ft_export(t_command_tree *tree, t_exec *exec)
{
    int i;

    i = 0;
    while (exec->env[i])
    {
        if (ft_strncmp(exec->env[i], tree->argument[1], ft_strlen(tree->argument[1])))
        {
            free(exec->env[i]);
            exec->env[i] = ft_strdup(tree->argument[1]);
            return (EXIT_SUCCESS);
        }
        i++;
    }
    exec->env = expand_env(exec);
    return (EXIT_SUCCESS);
}