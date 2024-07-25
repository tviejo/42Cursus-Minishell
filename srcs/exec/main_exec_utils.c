/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:59 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/25 18:43:15 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_node_left(t_command_tree *tree, t_data *exec)
{
	if (is_redir(tree) == true)
		ft_redir(tree, exec);
	else if (tree->type != nt_pipe)
	{
		dup2(exec->dupstdin, STDIN_FILENO);
		dup2(exec->dupstdout, STDOUT_FILENO);
	}
	exec->oldtype = tree->type;
	exec->side = e_left;
	exec_cmdtree(tree->left, exec);
	return (EXIT_SUCCESS);
}

int	exec_node_right(t_command_tree *tree, t_data *exec)
{
	if (is_redir(tree) == true)
		ft_redir(tree, exec);
	else if (tree->type != nt_pipe)
	{
		dup2(exec->dupstdin, STDIN_FILENO);
		dup2(exec->dupstdout, STDOUT_FILENO);
	}
	if (exec->error_code != 0 && tree->type == nt_AND)
		return (EXIT_FAILURE);
	else if (exec->error_code == 0 && tree->type == nt_OR)
		return (EXIT_FAILURE);
	exec->oldtype = tree->type;
	exec->side = e_right;
	exec_cmdtree(tree->right, exec);
	return (EXIT_SUCCESS);
}

bool	is_node(t_command_tree *tree)
{
	if (tree->type == nt_piped_cmd)
		return (false);
	else if (tree->type == nt_command)
		return (false);
	else
		return (true);
}

bool	is_redir(t_command_tree *tree)
{
	if (tree->type == nt_out_truncate)
		return (true);
	else if (tree->type == nt_out_append)
		return (true);
	else if (tree->type == nt_infile)
		return (true);
	else
		return (false);
}
