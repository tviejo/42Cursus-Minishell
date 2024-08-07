/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:53:18 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/07 19:10:15 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_all_process(t_data *exec)
{
	int			status;
	t_proccess	*process;

	process = exec->proccess;
	while (process && process->pid_index == -10)
		process = process->next;
	while (process && process->pid_index != -10)
	{
		while (process->pid_index > exec->max_pid)
			process = process->next;
		waitpid(exec->pid[process->pid_index], &status, 0);
		process->pid_index = -10;
		if (WIFEXITED(status))
		{
			exec->error_code = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			exec->error_code = 128 + WTERMSIG(status);
		}
		process = process->next;
	}
}

void	wait_subshell(t_data *exec)
{
	int			status;
	t_proccess	*process;

	process = exec->proccess;
	while (process && process->pid_index == -10)
		process = process->next;
	while (process && process->pid_index != -10)
	{
		while (process->pid_index < exec->max_pid)
			process = process->next;
		waitpid(exec->pid[process->pid_index], &status, 0);
		process->pid_index = -10;
		if (WIFEXITED(status))
		{
			exec->error_code = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			exec->error_code = 128 + WTERMSIG(status);
		}
		process = process->next;
	}
}
