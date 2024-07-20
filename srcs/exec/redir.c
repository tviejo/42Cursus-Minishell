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

char	*get_line(t_command_tree *tree, t_exec *exec)
{
	char	*output;
    int     nb_line;

    nb_line = 1;
	ft_putstr_fd(">", 1);
	output = get_next_line(STDIN_FILENO);
	while (output != NULL)
	{
		if (ft_strncmp(output, tree->argument[0],
				ft_strlen(tree->argument[0])) == 0)
		{
			free(output);
			exit(EXIT_SUCCESS);
		}
		write(exec->fdpipe[1], output, ft_strlen(output));
		ft_putstr_fd(">", 1);
		free(output);
		output = get_next_line(STDIN_FILENO);
        nb_line++;
	}
	printf("\nbash: warning: here-document at line %d ", nb_line);
	printf("delimited by end-of-file (wanted `%s')\n", tree->argument[0]);
    exit(EXIT_SUCCESS);
	return (output);
}

int	handle_here_doc(t_command_tree *tree, t_exec *exec)
{
	char	*output;
	int		index;

	create_pipe(exec, tree);
	index = create_fork(tree, exec);
	if (exec->pid[index] == 0)
	{
		close(exec->fdpipe[0]);
		output = get_line(tree, exec);
		free(output);
	}
	else
	{
		close(exec->fdpipe[1]);
		dup2(exec->fdpipe[0], STDIN_FILENO);
		close(exec->fdpipe[0]);
		wait(NULL);
	}
	return (EXIT_SUCCESS);
}
