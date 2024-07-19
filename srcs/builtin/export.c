# include "../includes/minishell.h"

bool is_env_var(char *env_var)
{
    int i;

    i = 0;
    while (env_var[i])
    {
        if (env_var[i] == '=')
            return (true);
        i++;
    }
    return (false);
}

int len_env_var(char *env_var)
{
    int i;

    i = 0;
    while (env_var[i] && env_var[i] != '=')
        i++;
    return (i);
}
int ft_export(t_command_tree *tree, t_exec *exec)
{
    int i;

    if (is_env_var(tree->argument[1]) == false)
        return (EXIT_FAILURE);
    i = 0;
    while (exec->env[i])
    {
        if (ft_strncmp(exec->env[i], tree->argument[1], len_env_var(tree->argument[1])) == 0)
        {
            free(exec->env[i]);
            exec->env[i] = ft_strdup(tree->argument[1]);
            return (EXIT_SUCCESS);
        }
        i++;
    }
    exec->env = expand_env(exec);
    exec->env[exec->env_len - 1] = ft_strdup(tree->argument[1]);
    return (EXIT_SUCCESS);
}