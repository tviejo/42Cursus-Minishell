/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:11:44 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/07 18:54:01 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_normal_subshell(t_command_tree *tree, t_data *exec)
{
	int		index;

	index = return_fork_index_subshell(exec);
	ft_lstadd_back_proccess(&exec->proccess, ft_lstnew_int(index));
	signal_handler_process();
	create_fork(tree, exec, index);
	if (exec->pid[index] == 0)
	{
		tree->subshell = ss_NO;
		exec->subshell = true;
		exec_cmdtree(tree, exec);
		ft_close_error(tree, exec);
		exit(exec->error_code);
	}
}

void	exec_piped_subshell(t_command_tree *tree, t_data *exec)
{
	int		index;
	int		fdpipe[2];

	index = return_fork_index_subshell(exec);
	ft_lstadd_back_proccess(&exec->proccess, ft_lstnew_int(index));
	pipe(fdpipe);
	signal_handler_process();
	create_fork(tree, exec, index);
	if (exec->pid[index] == 0)
	{
		close(fdpipe[0]);
		dup2(fdpipe[1], STDOUT_FILENO);
		close(fdpipe[1]);
		tree->subshell = ss_NO;
		exec->subshell = true;
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
		if (tree->subshell == ss_piped)
		{
			exec_piped_subshell(tree, exec);
		}
		else
		{
			exec_normal_subshell(tree, exec);
			wait_subshell(exec);
		}
	}
}
