/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:44 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/30 17:17:20 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	return_fork_index(t_data *exec)
{
	int	index;

	index = 0;
	while (exec->pid[index] != -10)
		index++;
	return (index);
}

int	create_fork(t_command_tree *tree, t_data *exec, int index)
{
	exec->pid[index] = fork();
	if (exec->pid[index] == -1)
		ft_close_error(tree, exec);
	return (index);
}
