#include "../includes/minishell.h"

int	store_env(t_exec *exec, char **env)
{
	int	i;

	if (!env)
		return (EXIT_FAILURE);
	i = 0;
	while (env[i] != NULL)
		i++;
	exec->env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		exec->env[i] = ft_strdup(env[i]);
		i++;
	}
    exec->env_len = i;
	exec->env[i] = NULL;
	return (EXIT_SUCCESS);
}
char **expand_env(t_exec *exec)
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
    new_env[i] = NULL;
	new_env[i + 1] = NULL;
	exec->env_len++;
    free_env(exec);
    return (new_env);
}

char	*find_path(char *name, t_exec *exec)
{
	int		i;

	i = 0;
	while (exec->env[i])
	{
		if (ft_strnstr(exec->env[i], name, ft_strlen(name)) != NULL)
		{
			return (&exec->env[i][ft_strlen(name)]);
		}
		i++;
	}
	return (NULL);
}

int    free_env(t_exec *exec)
{
    int i;
    int j;

    i = 0;
    while (exec->env[i] != NULL)
    {
        j = 0;
        free(exec->env[i]);
        i++;
    }
    free(exec->env);
    return (EXIT_SUCCESS);
}

int update_pwd(t_exec *exec, char *pwd)
{
    int i;

    i = 0;
    while (exec->env[i])
    {
        if (ft_strncmp(exec->env[i], "PWD=", 4) == 0)
        {
            free(exec->env[i]);
            exec->env[i] = ft_strjoin("PWD=", pwd);
            return (EXIT_SUCCESS);
        }
        i++;
    }
    return (EXIT_FAILURE);
}

