/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:55:13 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/09 21:19:27 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_data *exec, t_command_tree *tree)
{
	int	i;

	i = 0;
	if (tree->argument[1] != NULL)
	{
		ft_dprintf(2, CRED "env: '%s': %s\n" RESET, tree->argument[1], NO_FILES);
		exec->error_code = 127;
		return (EXIT_FAILURE);
	}
	while (exec->env[i])
	{
		ft_dprintf(1, "%s\n", exec->env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
