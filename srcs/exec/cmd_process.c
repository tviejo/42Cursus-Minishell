/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:19 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/06 19:02:46 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_process_and_or(t_command_tree *tree, t_data *exec)
{
	int	index;

	signal_handler_process();
	if (find_builtin(tree) > 0 && exec->oldtype != nt_pipe)
	{
		exec_builtin(tree, exec);
		return (EXIT_SUCCESS);
	}
	index = return_fork_index(exec);
	ft_lstadd_back_proccess(&exec->proccess, ft_lstnew_int(index));
	create_fork(tree, exec, index);
	if (exec->pid[index] == 0)
	{
		ft_lstclear_process(&exec->proccess);
		close_std_fd(exec);
		exec_cmd(tree, exec);
		exit(exec->error_code);
	}
	return (EXIT_SUCCESS);
}
