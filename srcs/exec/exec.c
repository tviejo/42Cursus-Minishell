#include "../includes/minishell.h"

/*
void	exec_error(t_pipex *pipex, char **argv, int argc)
{
	int	index;
	int	fd;

	index = 0;
	while (pipex->arguments[index] != NULL)
	{
		if (pipex->arguments[index][0] == NULL)
		{
			fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			close(fd);
		}
		index++;
	}
}
*/

static char *find_exec_cmd(t_command_tree *tree, t_data *exec)
{
	char	*tmp;
	char	*path;

	path = find_path_cmd(exec->env);
	if (path == NULL)
	{
		if (access(tree->argument[0], F_OK | X_OK) == 0)
			return (tree->argument[0]);
		printf("minishell: %s: No such file or directory\n", tree->argument[0]);
		free(path);
		exec->error_code = 127;
		ft_close_error(tree, exec);
		return (NULL);
	}
	tmp = find_cmd(tree->argument, ft_split(path, ':'));
	if (tmp == NULL)
	{
		printf("minishell: %s: command not found\n", tree->argument[0]);
		free(tmp);
		exec->error_code = 127;
		ft_close_error(tree, exec);
		return (NULL);
	}
	return (tmp);
}

void	exec_cmd(t_command_tree *tree, t_data *exec)
{
	char	*tmp;

	if (find_builtin(tree) > 0)
	{
		exec_builtin(tree, exec);
		return ;
	}
	else
	{
		tmp = find_exec_cmd(tree, exec);
		if (tmp == NULL)
		{
			free(tmp);
			exit(127);
		}
		else
		{
			execve(tmp, tree->argument, exec->env);
			free(tmp);
			perror("minishell: Error: ");
		}
	}
}
