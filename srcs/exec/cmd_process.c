/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:19 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/09 18:46:30 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	built_in_exe(t_command_tree *tree, t_data *exec)
{
	if (find_builtin(tree) > 0)
	{
		exec_builtin(tree, exec);
		return (true);
	}
	return (false);
}

int	cmd_process_and_or(t_command_tree *tree, t_data *exec)
{
	int		index;
	bool	built_in_executed;

	built_in_executed = false;
	signal_handler_process();
	if (do_all_redir(tree, exec) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else
		tree = get_next_command(tree);
	built_in_executed = built_in_exe(tree, exec);
	index = return_fork_index(exec);
	ft_lstadd_back_proccess(&exec->proccess, ft_lstnew_int(index));
	create_fork(tree, exec, index);
	if (exec->pid[index] == 0)
	{
		ft_lstclear_process(&exec->proccess);
		close_std_fd(exec);
		if (built_in_executed == false)
			exec_cmd(tree, exec);
		ft_close_error(tree, exec);
		exit(exec->error_code);
	}
	return (EXIT_SUCCESS);
}
