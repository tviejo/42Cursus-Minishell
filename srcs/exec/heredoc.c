#include "../includes/minishell.h"

char	*open_here_document(int *fd)
{
	int		nb;
	char	*name;
	char	*number;

	nb = 1;
	number = ft_itoa(nb);
	name = ft_strjoin("/tmp/here-document-", number);
	*fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	free(number);
	while (fd < 0)
	{
		nb++;
		number = ft_itoa(nb);
		free(name);
		name = ft_strjoin("/tmp/here-document-", number);
		*fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
		free(number);
	}
	return (name);
}

int	get_line(t_command_tree *tree, int fd)
{
	char	*output;
	int		nb_line;
	bool	warning;

	nb_line = 1;
	warning = true;
	ft_putstr_fd(">", 1);
	output = get_next_line(STDIN_FILENO);
	while (output != NULL)
	{
		if (ft_strncmp(output, tree->argument[0],
				ft_strlen(tree->argument[0])) == 0)
		{
			warning = false;
			break ;
		}
		write(fd, output, ft_strlen(output));
		ft_putstr_fd(">", 1);
		free(output);
		output = get_next_line(STDIN_FILENO);
		nb_line++;
	}
	free(output);
	close(fd);
	if (warning == true)
	{
		printf("\nbash: warning: here-document at line %d ", nb_line);
		printf("delimited by end-of-file (wanted `%s')\n", tree->argument[0]);
	}
	return (1);
}

char	*handle_here_doc(t_command_tree *tree, t_exec *exec)
{
	int		index;
	int		fd;
	char	*name;

	name = open_here_document(&fd);
	index = create_fork(tree, exec);
	if (exec->pid[index] == 0)
	{
		get_line(tree, fd);
		exit(0);
	}
	else
	{
		wait(NULL);
	}
	close(fd);
	return (name);
}

int	here_doc(t_command_tree *tree, t_exec *exec)
{
	char *name;
	int fd;

	name = handle_here_doc(tree, exec);
	fd = open(name, O_RDONLY, 0644);
	dup2(fd, STDIN_FILENO);
	close(fd);
	free(name);
	return (EXIT_SUCCESS);
}