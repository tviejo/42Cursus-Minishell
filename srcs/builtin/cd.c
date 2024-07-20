#include "../includes/minishell.h"

int	update_oldpwm(t_exec *exec)
{
	int		i;
	char	*pwd;

	pwd = find_path("PWD=", exec);
	if (pwd == NULL)
	{
		ft_putstr_fd("minishell: cd: PWD not set\n", 2);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (exec->env[i])
	{
		if (ft_strncmp(exec->env[i], "OLDPWD=", 7) == 0)
		{
			free(exec->env[i]);
			exec->env[i] = ft_strjoin("OLDPWD=", pwd);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	cd_go_home(t_exec *exec)
{
	char	*pwd;

	pwd = find_path("HOME=", exec);
	if (pwd == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (EXIT_FAILURE);
	}
	update_pwd(exec, pwd);
	chdir(pwd);
	return (EXIT_SUCCESS);
}

int	cd_go_back(t_exec *exec)
{
	char	*oldpwd;
	int		i;

	oldpwd = find_path("PWD=", exec);
	if (oldpwd == NULL)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (EXIT_FAILURE);
	}
	i = ft_strlen(oldpwd) - 2;
	while (oldpwd[i] != '/' && i >= 0)
	{
		oldpwd[i] = '\0';
		i--;
	}
	if (oldpwd[i] == '\0')
	{
		ft_putstr_fd("minishell: cd: PWD not set\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	cd_go_path(t_exec *exec, char *path)
{
	char	*pwd1;
    char	*pwd2;

	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
    pwd1 = ft_strjoin(find_path("PWD=", exec), "/");
	pwd2 = ft_strjoin(pwd1, path);
    free(pwd1);
	update_pwd(exec, pwd2);
    free(pwd2);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_command_tree *tree, t_exec *exec)
{
	if (tree->argument[1] == NULL)
	{
        update_oldpwm(exec);
		cd_go_home(exec);
		return (EXIT_SUCCESS);
	}
	else if (ft_strncmp(tree->argument[1], "..", 2) == 0)
	{
        update_oldpwm(exec);
		cd_go_back(exec);
		return (EXIT_SUCCESS);
	}
	else
	{
        update_oldpwm(exec);
		cd_go_path(exec, tree->argument[1]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
