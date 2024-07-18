#include "../includes/minishell.h"

int	store_env(t_exec *exec, char **env)
{
	int	i;

	if (!env)
		return (EXIT_FAILURE);
	i = 0;
	while (env[i])
		i++;
	exec->env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		exec->env[i] = ft_strdup(env[i]);
		i++;
	}
	exec->env[i] = NULL;
	return (EXIT_SUCCESS);
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

int	update_oldpwm(t_exec *exec)
{
	char *oldpwd;
	char *pwd;

	oldpwd = find_path("PWD=", exec);
	if (oldpwd == NULL)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (EXIT_FAILURE);
	}
	pwd = find_path("PWD=", exec);
	if (pwd == NULL)
	{
		ft_putstr_fd("minishell: cd: PWD not set\n", 2);
		return (EXIT_FAILURE);
	}
	oldpwd = ft_strdup(pwd);
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

int     print_env(t_exec *exec)
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
