/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:53:14 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/08 11:16:36 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_outfile(t_command_tree *tree, t_data *exec)
{
	if (tree->type == nt_out_append)
		exec->outfile = open(tree->argument[0], O_WRONLY | O_CREAT | O_APPEND,
				0644);
	else
		exec->outfile = open(tree->argument[0], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	if (exec->outfile == -1)
	{
		ft_dprintf(2, "minishell: %s: Permission denied\n", tree->argument[0]);
		exec->error_code = 1;
	}
	dup2(exec->outfile, STDOUT_FILENO);
	close(exec->outfile);
	return (EXIT_SUCCESS);
}

int	redir_infile(t_command_tree *tree, t_data *exec)
{
	exec->infile = open(tree->argument[0], O_RDONLY);
	if (exec->infile == -1)
	{
		ft_dprintf(2, "minishel: %s: %s\n", tree->argument[0], NO_FILES);
		exec->error_code = 1;
		return (EXIT_FAILURE);
	}
	dup2(exec->infile, STDIN_FILENO);
	close(exec->infile);
	return (EXIT_SUCCESS);
}
