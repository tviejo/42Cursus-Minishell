/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:29 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/30 17:20:43 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_and_or(t_command_tree *tree)
{
	if (tree->type == nt_AND || tree->type == nt_OR)
		return (true);
	return (false);
}

void	ft_lstclear_process(t_proccess **process)
{
	t_proccess	*process2;
	t_proccess	*temp;

	if (*process == NULL)
		return ;
	process2 = *process;
	while (process2->next != NULL)
	{
		temp = process2->next;
		free(process2);
		process2 = temp;
	}
	free(process2);
	*process = NULL;
}
