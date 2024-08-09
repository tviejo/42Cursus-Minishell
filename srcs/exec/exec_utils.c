/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:26 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/09 13:51:16 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/ioctl.h>

void	*ft_calloc_pid(t_command_tree *tree, t_data *exec)
{
	exec->pid = ft_calloc((tree->nb_command + 5) * 3, sizeof(pid_t));
	if (exec->pid == NULL)
		ft_close_error(tree, exec);
	ft_memset(exec->pid, -10, (tree->nb_command + 5) * 3);
	exec->pid_len = tree->nb_command + 5 * 3;
	exec->oldtype = nt_command;
	exec->side = e_left;
	return (exec->pid);
}

int	create_pipe(t_data *exec, t_cmdtree *tree)
{
	if (pipe(exec->fdpipe) == -1)
	{
		ft_close_error(tree, exec);
	}
	return (EXIT_SUCCESS);
}

int	close_pipe(t_data *exec)
{
	if (exec->fdpipe[0] > 2)
		close(exec->fdpipe[0]);
	if (exec->fdpipe[1] > 2)
		close(exec->fdpipe[1]);
	return (EXIT_SUCCESS);
}

int	duplicate_pipe(t_command_tree *tree, t_data *exec, int fdpipe, int mode)
{
	if (mode == 1)
	{
		if (dup2(fdpipe, STDOUT_FILENO) == -1)
			ft_close_error(tree, exec);
		close(fdpipe);
	}
	else
	{
		if (dup2(exec->fdpipe[0], STDIN_FILENO) == -1)
			ft_close_error(tree, exec);
		close(fdpipe);
	}
	return (EXIT_SUCCESS);
}

int	close_fd(int fd, t_command_tree *tree, t_data *exec)
{
	if (fd >= 0 && fd <= 1024)
	{
		if (close(fd) == -1)
		{
			ft_close_error(tree, exec);
		}
	}
	return (-1);
}
