/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:53:02 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/07 17:14:53 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_is_cmd(t_command_tree *tree, t_data *exec)
{
	if (tree->type == nt_piped_cmd && exec->end == false)
		child_process(tree, exec);
	else if (exec->oldtype == nt_pipe && exec->end == false)
	{
		last_child_process(tree, exec);
		wait_all_process(exec);
	}
	else if (exec->end == false)
	{
		cmd_process_and_or(tree, exec);
		wait_all_process(exec);
	}
}

void	ft_redir(t_command_tree *tree, t_data *exec)
{
	if (tree->type == nt_out_truncate || tree->type == nt_out_append)
	{
		redir_outfile(tree, exec);
	}
	if (tree->type == nt_infile || tree->type == nt_here_doc)
	{
		redir_infile(tree, exec);
	}
}

int	exec_cmdtree(t_command_tree *tree, t_data *exec)
{
	if (tree == NULL || exec->end == true)
		return (EXIT_SUCCESS);
	if ((tree->type == nt_command || tree->type == nt_piped_cmd)
		&& exec->end == false)
		ft_is_cmd(tree, exec);
	if (tree->subshell >= ss_YES && exec->end == false)
		exec_subshell(tree, exec);
	else
	{
		if (is_node(tree) == true && tree->left != NULL
			&& tree->subshell == ss_NO && exec->end == false)
			exec_node_left(tree, exec);
		if (is_node(tree) == true && tree->right != NULL
			&& tree->subshell == ss_NO && exec->end == false)
			exec_node_right(tree, exec);
	}
	return (EXIT_SUCCESS);
}
