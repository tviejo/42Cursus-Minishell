/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:50 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/25 11:55:47 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (*fd < 0) // ajout indirection '*' devant fd (oubli ?)
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

	nb_line = 1;
	signal(SIGINT, signal_handler_here_doc);
	output = readline("> ");
	while (output != NULL && ft_strncmp(output, tree->argument[0],
			ft_strlen(tree->argument[0])) != 0)
	{
		write(fd, output, ft_strlen(output));
		write(fd, "\n", 1);
		free(output);
		output = readline("> ");
		nb_line++;
	}
	if (output == NULL)
	{
		printf("minishell: warning: here-document at line %d ", nb_line);
		printf("delimited by end-of-file (wanted `%s')\n", tree->argument[0]);
	}
	free(output);
	close(fd);
	return (1);
}

char	*handle_here_doc(t_command_tree *tree, t_data *exec)
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

int	here_doc(t_command_tree *tree, t_data *exec)
{
	char	*name;
	int		fd;

	name = handle_here_doc(tree, exec);
	fd = open(name, O_RDONLY, 0644);
	dup2(fd, STDIN_FILENO);
	close(fd);
	free(name);
	return (EXIT_SUCCESS);
}
