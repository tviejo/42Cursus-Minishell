/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:55:34 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/10 11:34:27 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_close_error(t_command_tree *tree, t_data *exec)
{
	(void)tree;
	ft_free_pid(exec);
	close_std_fd(exec);
	if (exec->cmdtree != NULL)
		free_cmdtree(exec);
	free_env(exec);
	free_parsing(exec);
	ft_lstclear_process(&exec->proccess);
	return (EXIT_FAILURE);
}
