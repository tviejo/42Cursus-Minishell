/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:11:44 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/03 15:10:47 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_normal_subshell(t_command_tree *tree, t_data *exec)
{
	int		index;
	int		dupstdin;
	int		dupstdout;

	ft_dprintf(2, "exec_normal_subshell\n");
	dupstdin = dup(STDIN_FILENO);
	dupstdout = dup(STDOUT_FILENO);
	index = return_fork_index(exec);
	ft_lstadd_back_proccess(&exec->proccess, ft_lstnew_int(index));
	create_fork(tree, exec, index);
	if (exec->pid[index] == 0)
	{
		exec_cmdtree(tree, exec);
		close(dupstdin);
		close(dupstdout);
		ft_close_error(tree, exec);
		exit(exec->error_code);
	}
	else
	{
		dup2(dupstdin, STDIN_FILENO);
		dup2(dupstdout, STDOUT_FILENO);
		close(dupstdout);
		close(dupstdin);
	}
}

void exec_piped_subshell(t_command_tree *tree, t_data *exec)
{
	int		index;
	int		dupstdin;
	int		dupstdout;
	int fdpipe[2];

	dupstdin = dup(STDIN_FILENO);
	dupstdout = dup(STDOUT_FILENO);
	index = return_fork_index(exec);
	ft_lstadd_back_proccess(&exec->proccess, ft_lstnew_int(index));
	create_fork(tree, exec, index);
	pipe(fdpipe);
	if (exec->pid[index] == 0)
	{
		close(fdpipe[0]);
		dup2(fdpipe[1], STDOUT_FILENO);
		close(fdpipe[1]);
		exec_cmdtree(tree, exec);
		close(dupstdin);
		close(dupstdout);
		ft_close_error(tree, exec);
		exit(exec->error_code);
	}
	else
	{
		dup2(fdpipe[0], STDIN_FILENO);
		close(fdpipe[0]);
		close(fdpipe[1]);
		dup2(dupstdin, STDIN_FILENO);
		dup2(dupstdout, STDOUT_FILENO);
		close(dupstdout);
		close(dupstdin);
	}
}

void exec_subshell(t_command_tree *tree, t_data *exec)
{
	if (tree->subshell == true)
	{
		tree->subshell = false;
		if (exec->oldtype == nt_piped_cmd)
			exec_piped_subshell(tree, exec);
		else
			exec_normal_subshell(tree, exec);
	}
}
