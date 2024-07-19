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

void	exec_cmd(t_command_tree *tree, t_exec *exec, char **argument)
{
	if (argument == NULL)
		ft_close_error(tree, exec);
	if (argument[0] != NULL)
	{
		execve(argument[0], argument, exec->env);
		perror("Error");
	}
}
