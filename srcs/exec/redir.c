#include "../includes/minishell.h"

int	redir_outfile(t_command_tree *tree, t_exec *exec)
{
	int	fd;

	if (tree->type == nt_out_append)
		fd = open(tree->argument[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(tree->argument[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("open failed\n", 2);
		ft_close_error(tree, exec);
		return (EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

int	redir_infile(t_command_tree *tree, t_exec *exec)
{
	int	fd;

	fd = open(tree->argument[0], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("open failed\n", 2);
		ft_close_error(tree, exec);
		return (EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}
