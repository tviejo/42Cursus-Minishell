/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:53:18 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/25 11:53:20 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	wait_one_process(t_data *exec, int index)
{
	int	status;

	status = 0;
	waitpid(exec->pid[index], &status, 0);
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

	status = 0;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
		{
			exec->error_code = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			exec->error_code = 128 + WTERMSIG(status);
		}
	}
}
