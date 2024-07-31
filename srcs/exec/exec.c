/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:32 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/30 17:03:12 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_no_file_error(t_command_tree *tree)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tree->argument[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

static void	print_command_not_found_error(t_command_tree *tree)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tree->argument[0], 2);
	ft_putstr_fd(": command not found\n", 2);
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
		print_no_file_error(tree);
		free(path);
		exec->error_code = 127;
		ft_close_error(tree, exec);
		return (NULL);
	}
	tmp = find_cmd(tree->argument, ft_split(path, ':'));
	if (tmp == NULL)
	{
		exec->error_code = 127;
		print_command_not_found_error(tree);
		free(tmp);
		ft_close_error(tree, exec);
		return (NULL);
	}
	return (tmp);
}

static void	normal_exec(t_command_tree *tree, t_data *exec)
{
	char	*tmp;

	tmp = find_exec_cmd(tree, exec);
	if (tmp == NULL)
	{
		close_std_fd(exec);
		exit(exec->error_code);
	}
	else
	{
		close_std_fd(exec);
		execve(tmp, tree->argument, exec->env);
		free(tmp);
		perror("minishell: Error: ");
	}
}

void	exec_cmd(t_command_tree *tree, t_data *exec)
{
	if (find_builtin(tree) > 0)
	{
		exec_builtin(tree, exec);
		close_std_fd(exec);
		exit(exec->error_code);
	}
	else
	{
		normal_exec(tree, exec);
	}
}
