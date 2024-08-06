/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:11:44 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/06 17:45:13 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_normal_subshell(t_command_tree *tree, t_data *exec)
{
	int		index;

	index = return_fork_index(exec);
	ft_lstadd_back_proccess(&exec->proccess, ft_lstnew_int(index));
	create_fork(tree, exec, index);
	if (exec->pid[index] == 0)
	{
		exec_cmdtree(tree, exec);
		ft_close_error(tree, exec);
		exit(exec->error_code);
	}
}

void	exec_piped_subshell(t_command_tree *tree, t_data *exec)
{
	int		index;
	int		fdpipe[2];

	index = return_fork_index(exec);
	ft_lstadd_back_proccess(&exec->proccess, ft_lstnew_int(index));
	pipe(fdpipe);
	create_fork(tree, exec, index);
	if (exec->pid[index] == 0)
	{
		close(fdpipe[0]);
		dup2(fdpipe[1], STDOUT_FILENO);
		close(fdpipe[1]);
		exec_cmdtree(tree, exec);
		exit(exec->error_code);
	}
	else
	{
		dup2(fdpipe[0], STDIN_FILENO);
		close(fdpipe[0]);
		close(fdpipe[1]);
	}
}

void	exec_subshell(t_command_tree *tree, t_data *exec)
{
	if (is_redir(tree) == true)
		ft_redir(tree, exec);
	if (tree->subshell >= ss_YES)
	{
		exec->subshell = true;
		if (tree->subshell == ss_piped)
		{
			tree->subshell = ss_NO;
			exec_piped_subshell(tree, exec);
		}
		else
		{
			tree->subshell = ss_NO;
			exec_normal_subshell(tree, exec);
			wait_all_process(exec);
		}
	}
}

void	ft_redirect_subshell(t_data *exec)
{
	if (exec->subshell_infile != NULL && exec->redirected_infile == false)
	{
		exec->infile = open(exec->subshell_infile, O_RDONLY, 0644);
		if (exec->outfile == -1)
		{
			exec->error_code = 1;
			exec->end = true;
		}
		dup2(exec->infile, STDIN_FILENO);
		close(exec->infile);
	}
	if (exec->subshell_outfile != NULL && exec->redirected_outfile == false)
	{
		exec->outfile = open(exec->subshell_outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (exec->outfile == -1)
		{
			exec->error_code = 1;
			exec->end = true;
		}
		dup2(exec->outfile, STDOUT_FILENO);
		close(exec->outfile);
	}
}
