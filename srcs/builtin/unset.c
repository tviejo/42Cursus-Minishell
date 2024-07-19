# include "../includes/minishell.h"

int ft_unset(t_command_tree *tree, t_exec *exec)
{
    int i;

    i = 0;
    while (exec->env[i] != NULL)
    {
        if (ft_strncmp(exec->env[i], tree->argument[1], ft_strlen(tree->argument[1])) == 0)
        {
            while (exec->env[i + 1] != NULL)
            {
                free(exec->env[i]);
                exec->env[i] = ft_strdup(exec->env[i + 1]);
                i++;
            }
            free(exec->env[i]);
            exec->env[i] = NULL;
            exec->env_len--;
        }
        i++;
    }
    return (EXIT_SUCCESS);
}