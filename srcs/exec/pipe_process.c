/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:53:10 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/27 23:14:50 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	child_process(t_command_tree *tree, t_data *exec)
{
	int	index;
	int fdpipe[2];

	signal_handler_process();
	index = return_fork_index(exec);
	ft_lstadd_back_proccess(&exec->proccess, ft_lstnew_int(index));
	pipe(fdpipe);
	create_fork(tree, exec, index);
	if (exec->pid[index] == 0)
	{
		close_std_fd(exec);
		close (fdpipe[0]);
		dup2(fdpipe[1], STDOUT_FILENO);
		close(fdpipe[1]);
		exec_cmd(tree, exec);
	}
	else
	{
		dup2(fdpipe[0], STDIN_FILENO);
		close(fdpipe[0]);
		close(fdpipe[1]);
	}
	return (EXIT_SUCCESS);
}

int	last_child_process(t_command_tree *tree, t_data *exec)
{
	int	index;
	int fdpipe[2];

	signal_handler_process();
	index = return_fork_index(exec);
	ft_lstadd_back_proccess(&exec->proccess, ft_lstnew_int(index));
	pipe(fdpipe);
	create_fork(tree, exec, index);
	if (exec->pid[index] == 0)
	{
		close_std_fd(exec);
		close (fdpipe[1]);
		close (fdpipe[0]);
		exec_cmd(tree, exec);
	}
	else
	{
		dup2(fdpipe[0], STDIN_FILENO);
		close(fdpipe[0]);
		close(fdpipe[1]);
	}
	return (exec->error_code);
}
