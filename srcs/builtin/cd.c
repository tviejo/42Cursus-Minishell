/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:55:05 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/02 13:47:23 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	update_oldpwm(t_data *exec)
{
	int		i;
	char	*pwd;
	char	buffer[4096];

	pwd = getcwd(buffer, 4096);
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
	if (exec->env[i] == NULL)
		exec->env = add_back_env(exec, ft_strjoin("OLDPWD=", pwd));
	return (EXIT_SUCCESS);
}

int	cd_go_home(t_data *exec)
{
	char	*pwd;

	pwd = find_path("HOME=", exec);
	if (pwd == NULL)
	{
		ft_dprintf(2, "%scd: HOME not set\n", MINI);
		exec->error_code = 1;
		return (EXIT_FAILURE);
	}
	update_pwd(exec, pwd);
	chdir(pwd);
	return (EXIT_SUCCESS);
}

int	cd_go_path(t_data *exec, char *path)
{
	char	pwd[4096];
	char	*pwd2;

	if (chdir(path) == -1)
	{
		ft_dprintf(2, "cd: %s: %s\n", path, NO_FILES);
		exec->error_code = 1;
		return (EXIT_FAILURE);
	}
	pwd2 = ft_strjoin("PWD=", getcwd(pwd, 4096));
	update_pwd(exec, pwd2);
	free(pwd2);
	return (EXIT_SUCCESS);
}

int	cd_go_back(t_data *exec)
{
	char	*pwd;
	int		i;

	i = 0;
	while (exec->env[i])
	{
		if (ft_strncmp(exec->env[i], "OLDPWD=", 7) == 0)
		{
			pwd = ft_strdup(exec->env[i] + 7);
			break ;
		}
		i++;
	}
	if (exec->env[i] == NULL)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		exec->error_code = 1;
		return (EXIT_FAILURE);
	}
	update_oldpwm(exec);
	update_pwd(exec, pwd);
	chdir(pwd);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_command_tree *tree, t_data *exec)
{
	if (tree->argument[1] != NULL && tree->argument[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		exec->error_code = 1;
		return (EXIT_FAILURE);
	}
	else if (tree->argument[1] == NULL)
	{
		update_oldpwm(exec);
		cd_go_home(exec);
		return (EXIT_SUCCESS);
	}
	else if (ft_strncmp(tree->argument[1], "-", 1) == 0)
	{
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
