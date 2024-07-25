/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:53:10 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/25 14:18:31 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	child_process(t_command_tree *tree, t_data *exec)
{
	int	index;

	signal_handler_process();
	create_pipe(exec, tree);
	index = create_fork(tree, exec);
	if (exec->pid[index] == 0)
	{
		close_std_fd(exec);
		exec->fdpipe[0] = close_fd(exec->fdpipe[0], tree, exec);
		duplicate_pipe(tree, exec, 1);
		exec_cmd(tree, exec);
	}
	else
	{
		exec->fdpipe[1] = close_fd(exec->fdpipe[1], tree, exec);
		duplicate_pipe(tree, exec, 2);
		exec->fdpipe[0] = close_fd(exec->fdpipe[0], tree, exec);
	}
	close_pipe(exec);
	return (EXIT_SUCCESS);
}

int	last_child_process(t_command_tree *tree, t_data *exec)
{
	int	index;

	signal_handler_process();
	index = create_fork(tree, exec);
	if (exec->pid[index] == 0)
	{
		close_std_fd(exec);
		exec_cmd(tree, exec);
	}
	return (exec->error_code);
}
