/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:53:02 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/03 18:58:48 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_is_cmd(t_command_tree *tree, t_data *exec)
{
	if (tree->type == nt_piped_cmd && exec->error_code == 0)
	{
		child_process(tree, exec);
	}
	else if (exec->oldtype == nt_pipe && exec->error_code == 0)
	{
		last_child_process(tree, exec);
		wait_all_process(exec);
	}
	else if (exec->error_code == 0 || exec->oldtype == nt_OR)
	{
		cmd_process_and_or(tree, exec);
		wait_all_process(exec);
	}
	else
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
	// static int index = 0;

	// ft_dprintf(2, "exec_cmdtree\n");
	// if (index == 0)
	// {
	// 	tree->subshell = true;
	// 	index = 1;
	// }
	if (tree == NULL)
		return (EXIT_SUCCESS);
	else if (tree->type == nt_command || tree->type == nt_piped_cmd)
		ft_is_cmd(tree, exec);
	if (is_node(tree) == true && tree->left != NULL && tree->subshell == ss_NO)
		exec_node_left(tree, exec);
	if (is_node(tree) == true && tree->right != NULL && tree->subshell == ss_NO)
		exec_node_right(tree, exec);
	if (tree->subshell >= ss_YES)
		exec_subshell(tree, exec);
	return (EXIT_SUCCESS);
}
