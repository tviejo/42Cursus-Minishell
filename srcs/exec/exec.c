/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:32 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/09 22:02:51 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	directory_error(t_command_tree *tree, t_data *exec, bool no_files)
{
	if (no_files == true)
	{
		ft_dprintf(2, CRED "%s%s: %s\n" RESET, MINI, tree->argument[0],
			NO_FILES);
		ft_close_error(tree, exec);
		exec->error_code = 127;
		exit(exec->error_code);
	}
	else
	{
		ft_dprintf(2, CRED "%s%s: %s\n" RESET, MINI, tree->argument[0], IS_DIR);
		ft_close_error(tree, exec);
		exec->error_code = 126;
		exit(exec->error_code);
	}
}

static void	is_a_directory(char *path, t_data *exec, t_command_tree *tree)
{
	struct stat	buf;

	if (stat(path, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
			directory_error(tree, exec, false);
		else
			directory_error(tree, exec, true);
	}
	else
		directory_error(tree, exec, true);
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
		ft_dprintf(2, CRED "%s%s: %s\n" RESET, MINI, tree->argument[0],
			NO_FILES);
		free(path);
		return (NULL);
	}
	tmp = find_cmd(tree->argument, ft_split(path, ':'));
	return (tmp);
}

static void	normal_exec(t_command_tree *tree, t_data *exec)
{
	char	*tmp;

	tmp = find_exec_cmd(tree, exec);
	if (tmp == NULL)
	{
		free(tmp);
		ft_close_error(tree, exec);
		exec->error_code = 127;
		exit(exec->error_code);
	}
	else
	{
		exec->error_code = execve(tmp, tree->argument, exec->env);
		if (errno == EACCES)
			is_a_directory(tree->argument[0], exec, tree);
		else
			perror("minishell");
		ft_close_error(tree, exec);
		free(tmp);
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
