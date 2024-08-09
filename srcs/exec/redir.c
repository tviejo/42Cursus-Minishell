/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:53:14 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/09 14:05:14 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	do_all_redir(t_command_tree *tree, t_data *exec)
{
	while (tree != NULL && is_redir(tree) == true && tree->subshell == ss_NO)
	{
		if (ft_redir(tree, exec) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		tree = tree->right;
	}
	return (EXIT_SUCCESS);
}

t_command_tree	*get_next_command(t_command_tree *tree)
{
	if (tree->type == nt_command || tree->type == nt_piped_cmd)
		return (tree);
	if (tree->right != NULL)
		return (get_next_command(tree->right));
	return (tree);
}

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
