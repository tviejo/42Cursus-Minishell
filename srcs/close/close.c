/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:55:34 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/05 20:01:36 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_close_error(t_command_tree *tree, t_data *exec)
{
	(void)tree;
	ft_free_pid(exec);
	close_std_fd(exec);
	free_cmdtree(exec);
	free_env(exec);
	free_parsing(exec);
	ft_lstclear_process(&exec->proccess);
	return (EXIT_FAILURE);
}
