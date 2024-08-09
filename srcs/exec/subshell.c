/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:11:44 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/09 18:41:36 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_command_tree	*get_next_subshell(t_command_tree *tree)
{
	while (tree->subshell == ss_NO)
		tree = tree->right;
	return (tree);
}

void	exec_normal_subshell(t_command_tree *tree, t_data *exec)
{
	int		index;

	index = return_fork_index_subshell(exec);
	ft_lstadd_back_proccess(&exec->proccess, ft_lstnew_int(index));
	signal_handler_process();
	create_fork(tree, exec, index);
	if (exec->pid[index] == 0)
	{
		if (do_all_redir(tree, exec) == EXIT_FAILURE)
			exit(exec->error_code);
		else
			tree = get_next_subshell(tree);
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
		if (do_all_redir(tree, exec) == EXIT_FAILURE)
			exit(exec->error_code);
		else
			tree = get_next_subshell(tree);
		tree->subshell = ss_NO;
		exec->subshell = true;
		exec_cmdtree(tree, exec);
		ft_close_error(tree, exec);
		exit(exec->error_code);
	}
	else
		close_pipe_2(fdpipe);
}

void	exec_subshell(t_command_tree *tree, t_data *exec)
{
	if (find_closest_subshell(tree) >= ss_YES)
	{
		if (find_closest_subshell(tree) == ss_piped)
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
