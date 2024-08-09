/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:53:10 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/09 19:38:11 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_pipe(int *fdpipe, t_data *exec)
{
	close_std_fd(exec);
	ft_lstclear_process(&exec->proccess);
	dup2(fdpipe[1], STDOUT_FILENO);
	close(fdpipe[1]);
	close(fdpipe[0]);
}

void	close_pipe_2(int *fdpipe)
{
	dup2(fdpipe[0], STDIN_FILENO);
	close(fdpipe[0]);
	close(fdpipe[1]);
}

int	child_process(t_command_tree *tree, t_data *exec)
{
	int	index;
	int	fdpipe[2];

	signal_handler_process();
	index = return_fork_index(exec);
	ft_lstadd_back_proccess(&exec->proccess, ft_lstnew_int(index));
	pipe(fdpipe);
	create_fork(tree, exec, index);
	if (exec->pid[index] == 0)
	{
		init_pipe(fdpipe, exec);
		if (do_all_redir(tree, exec) == EXIT_FAILURE)
			exit(exec->error_code);
		else
			tree = get_next_command(tree);
		exec_cmd(tree, exec);
		ft_close_error(tree, exec);
		exit(exec->error_code);
	}
	else
		close_pipe_2(fdpipe);
	return (EXIT_SUCCESS);
}

int	last_child_process(t_command_tree *tree, t_data *exec)
{
	int	index;
	int	fdpipe[2];

	signal_handler_process();
	index = return_fork_index(exec);
	ft_lstadd_back_proccess(&exec->proccess, ft_lstnew_int(index));
	pipe(fdpipe);
	create_fork(tree, exec, index);
	if (exec->pid[index] == 0)
	{
		close_std_fd(exec);
		ft_lstclear_process(&exec->proccess);
		close(fdpipe[0]);
		close(fdpipe[1]);
		if (do_all_redir(tree, exec) == EXIT_FAILURE)
			exit(exec->error_code);
		else
			tree = get_next_command(tree);
		exec_cmd(tree, exec);
		ft_close_error(tree, exec);
		exit(exec->error_code);
	}
	else
		close_pipe_2(fdpipe);
	return (exec->error_code);
}
