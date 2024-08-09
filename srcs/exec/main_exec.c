/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:53:02 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/09 14:05:36 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	find_closest_type(t_command_tree *tree)
{
	if (tree->type == nt_command || tree->type == nt_piped_cmd)
		return (tree->type);
	if (tree->right != NULL)
		return (find_closest_type(tree->right));
	return (tree->type);
}

int	find_closest_subshell(t_command_tree *tree)
{
	if (tree->subshell >= ss_YES)
		return (tree->subshell);
	if (tree->subshell == ss_NO && (tree->type == nt_command
			|| tree->type == nt_piped_cmd))
		return (tree->subshell);
	if (tree->right != NULL)
		return (find_closest_subshell(tree->right));
	return (tree->subshell);
}

void	ft_is_cmd(t_command_tree *tree, t_data *exec)
{
	if (find_closest_subshell(tree) >= ss_YES)
		exec_subshell(tree, exec);
	else if (find_closest_type(tree) == nt_piped_cmd)
		child_process(tree, exec);
	else if (exec->oldtype == nt_pipe)
	{
		last_child_process(tree, exec);
		wait_all_process(exec);
	}
	else
	{
		cmd_process_and_or(tree, exec);
		wait_all_process(exec);
	}
}

int	ft_redir(t_command_tree *tree, t_data *exec)
{
	if (tree->type == nt_out_truncate || tree->type == nt_out_append)
	{
		return (redir_outfile(tree, exec));
	}
	if (tree->type == nt_infile || tree->type == nt_here_doc)
	{
		return (redir_infile(tree, exec));
	}
	return (EXIT_SUCCESS);
}

int	exec_cmdtree(t_command_tree *tree, t_data *exec)
{
	if (tree == NULL)
		return (EXIT_SUCCESS);
	if (is_redir(tree) == true && find_closest_subshell(tree) == ss_NO
		&& find_closest_type(tree) != nt_piped_cmd
		&& find_closest_type(tree) != nt_command)
		ft_redir(tree, exec);
	else if (tree->subshell >= ss_YES || tree->type == nt_command
		|| tree->type == nt_piped_cmd || is_redir(tree) == true)
		ft_is_cmd(tree, exec);
	else
	{
		if (is_node(tree) == true && is_redir(tree) == false
			&& tree->left != NULL)
			exec_node_left(tree, exec);
		if (is_node(tree) == true && is_redir(tree) == false
			&& tree->right != NULL)
			exec_node_right(tree, exec);
	}
	return (EXIT_SUCCESS);
}
