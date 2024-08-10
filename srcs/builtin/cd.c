/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:55:05 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/10 15:41:09 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	update_oldpwm(t_data *exec)
{
	int		i;
	char	*pwd;
	char	buffer[4096];
	char	*tmp;

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
	{
		tmp = ft_strjoin("OLDPWD=", pwd);
		exec->env = add_back_env(exec, tmp);
		free(tmp);
	}
	return (EXIT_SUCCESS);
}

int	cd_go_home(t_data *exec)
{
	char	*pwd;

	pwd = find_path("HOME=", exec);
	if (pwd == NULL)
	{
		ft_dprintf(2, CRED "%scd: HOME not set\n" RESET, MINI);
		exec->error_code = 1;
		return (EXIT_FAILURE);
	}
	update_pwd(exec, pwd);
	chdir(pwd);
	return (EXIT_SUCCESS);
}

int	cd_go_path(t_data *exec, char *path)
{
	char		pwd[4096];
	char		*pwd2;
	struct stat	buf;

	if (chdir(path) != 0)
	{
		if (stat(path, &buf) == 0)
			ft_dprintf(2, CRED "cd: %s: %s\n" RESET, path, NOT_DIR);
		else
			ft_dprintf(2, CRED "cd: %s: %s\n" RESET, path, NO_FILES);
		exec->error_code = 1;
		return (EXIT_FAILURE);
	}
	getcwd(pwd, 4096);
	if (access(pwd, F_OK) == -1)
	{
		ft_dprintf(2, CRED "cd: %s: %s\n" RESET, path, NO_FILES);
		return (exec->error_code = 1, EXIT_FAILURE);
	}
	pwd2 = ft_strjoin("PWD=", pwd);
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
		ft_dprintf(2, CRED "%sminishell: cd: OLDPWD not set\n" RESET, MINI);
		return (exec->error_code = 1, EXIT_FAILURE);
	}
	update_oldpwm(exec);
	update_pwd(exec, pwd);
	chdir(pwd);
	if (access(pwd, F_OK) == -1)
		return (free(pwd), exec->error_code = 1, EXIT_FAILURE);
	return (free(pwd), EXIT_SUCCESS);
}

int	ft_cd(t_command_tree *tree, t_data *exec)
{
	if (tree->argument[1] != NULL && tree->argument[2] != NULL)
	{
		ft_dprintf(2, CRED "%sminishell: cd: too many arguments\n" RESET, MINI);
		exec->error_code = 1;
		return (EXIT_FAILURE);
	}
	else if (tree->argument[1] == NULL || ft_strncmp(tree->argument[1], "~\0",
			2) == 0)
	{
		update_oldpwm(exec);
		cd_go_home(exec);
		return (EXIT_SUCCESS);
	}
	else if (ft_strncmp(tree->argument[1], "-\0", 2) == 0)
		return (cd_go_back(exec), EXIT_SUCCESS);
	else
	{
		update_oldpwm(exec);
		cd_go_path(exec, tree->argument[1]);
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
