/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:19 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/25 17:42:27 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_process_and_or(t_command_tree *tree, t_data *exec)
{
	int	index;

	signal_handler_process();
	if (find_builtin(tree) > 0)
	{
		exec_builtin(tree, exec);
		return (EXIT_SUCCESS);
	}
	index = create_fork(tree, exec);
	if (exec->pid[index] == 0)
	{
		exec_cmd(tree, exec);
	}
	return (EXIT_SUCCESS);
}
