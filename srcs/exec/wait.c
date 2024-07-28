/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:53:18 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/28 12:03:26 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	wait_one_process(t_data *exec)
{
	int	status;
	t_proccess *process;

	process = exec->proccess;
	status = 0;
	while (process != NULL && process->pid_index == -10)
		process = process->next;
	if (process == NULL)
		return (true);
	waitpid(exec->pid[process->pid_index], &status, WUNTRACED);
	process->pid_index = -10;
	if (WIFEXITED(status))
	{
		exec->error_code = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		exec->error_code = 128 + WTERMSIG(status);
	}
	return (true);
}

void	wait_all_process(t_data *exec)
{
	int	status;
	t_proccess *process;

	process = exec->proccess;
	status = 0;
	while (process != NULL && process->pid_index == -10)
		process = process->next;
	while (process)
	{
		waitpid(exec->pid[process->pid_index], &status, WUNTRACED);
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
