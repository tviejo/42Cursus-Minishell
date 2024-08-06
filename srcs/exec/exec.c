/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:32 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/06 19:06:38 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	directory_error(t_command_tree *tree, t_data *exec, bool no_files)
{
	if (no_files == true)
	{
		ft_dprintf(2, "%s%s: %s\n", MINI, tree->argument[0], NO_FILES);
		ft_close_error(tree, exec);
		exec->error_code = 127;
		exit(exec->error_code);
	}
	else
	{
		ft_dprintf(2, "%s%s: %s\n", MINI, tree->argument[0], IS_DIR);
		ft_close_error(tree, exec);
		exec->error_code = 126;
		exit(exec->error_code);
	}
}

static void	is_a_directory(char *tmp, t_data *exec, t_cmdtree *tree)
{
	int	nb_point;
	int	i;

	i = 0;
	nb_point = 0;
	while (tmp[i] != '\0' && (tmp[i] == '/' || tmp[i] == '.'))
	{
		if (tmp[i] == '.')
			nb_point++;
		else if (tmp[i] == '/')
			nb_point = 0;
		if (nb_point > 2)
			directory_error(tree, exec, true);
		i++;
	}
	if (tmp[i] == '\0')
		directory_error(tree, exec, false);
}

static char	*find_exec_cmd(t_command_tree *tree, t_data *exec)
{
	char	*tmp;
	char	*path;

	path = find_path_cmd(exec->env);
	if (path == NULL)
	{
		if (access(tree->argument[0], F_OK | X_OK) == 0)
			return (tree->argument[0]);
		ft_dprintf(2, "%s%s: %s\n", MINI, tree->argument[0], NO_FILES);
		free(path);
		exec->error_code = 127;
		ft_close_error(tree, exec);
		return (NULL);
	}
	tmp = find_cmd(tree->argument, ft_split(path, ':'));
	if (tmp == NULL)
	{
		exec->error_code = 127;
		ft_dprintf(2, "%s%s: command not found\n", MINI, tree->argument[0]);
		return (tmp);
	}
	return (tmp);
}

static void	normal_exec(t_command_tree *tree, t_data *exec)
{
	char	*tmp;

	if (tree->argument[0][0] == '/' || tree->argument[0][0] == '.')
		is_a_directory(tree->argument[0], exec, tree);
	tmp = find_exec_cmd(tree, exec);
	if (tmp == NULL)
	{
		free(tmp);
		ft_close_error(tree, exec);
		exit(exec->error_code);
	}
	else
	{
		exec->error_code = execve(tmp, tree->argument, exec->env);
		free(tmp);
		perror("minishell");
		exit(exec->error_code);
	}
}

void	exec_cmd(t_command_tree *tree, t_data *exec)
{
	if (find_builtin(tree) > 0)
	{
		exec_builtin(tree, exec);
		ft_close_error(tree, exec);
		exit(exec->error_code);
	}
	else
	{
		normal_exec(tree, exec);
	}
}
