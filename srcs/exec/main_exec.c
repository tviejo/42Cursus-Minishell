/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:53:02 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/05 20:05:44 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_redirect_subshell(t_data *exec)
{
	if (exec->subshell_infile != NULL && exec->redirected_infile == false)
	{
		exec->infile = open(exec->subshell_infile, O_RDONLY);
		dup2(exec->infile, STDIN_FILENO);
		close(exec->infile);
	}
	if (exec->subshell_outfile != NULL && exec->redirected_outfile == false)
	{
		exec->outfile = open(exec->subshell_outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(exec->outfile, STDOUT_FILENO);
		close(exec->outfile);
	}
}

void	ft_is_cmd(t_command_tree *tree, t_data *exec)
{
	if (exec->subshell == true && exec->oldtype != nt_pipe)
		ft_redirect_subshell(exec);
	if (tree->type == nt_piped_cmd && exec->error_code == 0
		&& exec->end == false)
		child_process(tree, exec);
	else if (exec->oldtype == nt_pipe && exec->error_code == 0
		&& exec->end == false)
	{
		last_child_process(tree, exec);
		wait_all_process(exec);
	}
	else if (exec->end == false)
	{
		cmd_process_and_or(tree, exec);
		wait_all_process(exec);
	}
	exec->redirected_infile = false;
	exec->redirected_outfile = false;
}

void	ft_redir(t_command_tree *tree, t_data *exec)
{
	if (tree->type == nt_out_truncate || tree->type == nt_out_append)
	{
		redir_outfile(tree, exec);
		if (exec->subshell == true)
			exec->redirected_outfile = true;
		else
			exec->subshell_outfile = tree->argument[0];
	}
	if (tree->type == nt_infile || tree->type == nt_here_doc)
	{
		redir_infile(tree, exec);
		if (exec->subshell == true)
			exec->redirected_infile = true;
		else
			exec->subshell_infile = tree->argument[0];
	}
}

int	exec_cmdtree(t_command_tree *tree, t_data *exec)
{
	if (tree == NULL || exec->end == true)
		return (EXIT_SUCCESS);
	if ((tree->type == nt_command || tree->type == nt_piped_cmd)
		&& exec->end == false)
		ft_is_cmd(tree, exec);
	if (is_node(tree) == true && tree->left != NULL && tree->subshell == ss_NO
		&& exec->end == false)
		exec_node_left(tree, exec);
	if (is_node(tree) == true && tree->right != NULL && tree->subshell == ss_NO
		&& exec->end == false)
		exec_node_right(tree, exec);
	if (tree->subshell >= ss_YES && exec->end == false)
		exec_subshell(tree, exec);
	return (EXIT_SUCCESS);
}
