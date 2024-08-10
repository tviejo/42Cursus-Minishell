/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:32 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/10 13:31:22 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	directory_error(t_command_tree *tree, t_data *exec, int type)
{
	if (type == DIR_2)
	{
		ft_dprintf(2, CRED "%s'%s': %s\n" RESET, MINI, tree->argument[0],
			IS_DIR);
		exec->error_code = 126;
	}
	else if (type == PERM)
	{
		ft_dprintf(2, CRED "%s'%s': %s\n" RESET, MINI, tree->argument[0],
			NO_PERM);
		exec->error_code = 126;
	}
	else if (type == CMD)
	{
		ft_dprintf(2, CRED "%s'%s': %s\n" RESET, MINI, tree->argument[0],
			NO_CMD);
		exec->error_code = 126;
	}
	else
	{
		ft_dprintf(2, CRED "%s'%s': %s\n" RESET, MINI, tree->argument[0],
			NO_FILES);
		exec->error_code = 127;
	}
}

static void	is_a_directory(char *path, t_data *exec, t_command_tree *tree,
		char *tmp)
{
	struct stat	buf;

	if (tmp == NULL || tmp[0] == '\0')
	{
		ft_dprintf(2, CRED "%s: '': %s\n" RESET, MINI, NO_CMD);
		exec->error_code = 127;
	}
	else if (stat(path, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
			directory_error(tree, exec, DIR_2);
		else if (access(path, X_OK) == -1)
			directory_error(tree, exec, PERM);
	}
	else if (contain_backslash(path) == true)
		directory_error(tree, exec, FILES);
	else
		directory_error(tree, exec, CMD);
}

static char	*find_exec_cmd(t_command_tree *tree, t_data *exec)
{
	char	*path;

	path = find_path_cmd(exec->env);
	if (path == NULL)
	{
		if (access(tree->argument[0], F_OK | X_OK) == 0)
			return (tree->argument[0]);
		ft_dprintf(2, CRED "%s'%s': %s\n" RESET, MINI, tree->argument[0],
			NO_FILES);
		free(path);
		return (NULL);
	}
	return (find_cmd(tree->argument, ft_split(path, ':')));
}

static void	normal_exec(t_command_tree *tree, t_data *exec)
{
	char	*tmp;

	tmp = find_exec_cmd(tree, exec);
	if (tmp == NULL)
	{
		ft_dprintf(2, CRED "%s'%s': %s\n" RESET, MINI, tree->argument[0],
			NO_CMD);
		free(tmp);
		ft_close_error(tree, exec);
		exec->error_code = 127;
		exit(exec->error_code);
	}
	else
	{
		execve(tmp, tree->argument, exec->env);
		if (errno == ENOENT || errno == EISDIR || errno == EACCES)
			is_a_directory(tree->argument[0], exec, tree, tmp);
		else
			ft_dprintf(2, CRED "%s'%s': %s\n" RESET, MINI, tree->argument[0],
				strerror(errno));
		ft_close_error(tree, exec);
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
