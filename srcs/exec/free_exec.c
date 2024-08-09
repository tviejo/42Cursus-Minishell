/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:47 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/09 17:16:48 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_free_pid(t_data *exec)
{
	if (exec->pid != NULL)
		free(exec->pid);
	return (EXIT_SUCCESS);
}
