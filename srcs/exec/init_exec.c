/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:56 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/25 11:54:52 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dup_std(t_data *exec)
{
	exec->dupstdin = dup(STDIN_FILENO);
	exec->dupstdout = dup(STDOUT_FILENO);
	if (exec->dupstdin == -1 || exec->dupstdout == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	close_std_fd(t_data *exec)
{
	if (exec->dupstdin != -1)
		close(exec->dupstdin);
	if (exec->dupstdout != -1)
		close(exec->dupstdout);
	return (EXIT_SUCCESS);
}

int	calloc_pid(t_data *exec, t_command_tree *tree)
{
	int	i;

	i = 0;
	exec->pid = (pid_t *)ft_calloc(sizeof(pid_t), tree->nb_command);
	if (exec->pid == NULL)
		ft_close_error(tree, exec);
	while (i < tree->nb_command)
	{
		exec->pid[i] = -10;
		i++;
	}
	return (EXIT_SUCCESS);
}
