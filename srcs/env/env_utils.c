# include "../includes/minishell.h"

char    **add_back_env(t_data *exec, char *env_var)
{
    int i;
    char **new_env;

    i = 0;
    new_env = malloc(sizeof(char *) * (exec->env_len + 2));
    while (exec->env[i])
    {
        new_env[i] = ft_strdup(exec->env[i]);
        i++;
    }
    new_env[i] = ft_strdup(env_var);
    new_env[i + 1] = NULL;
    exec->env_len++;
    free_env(exec);
    return (new_env);
}