/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:55:29 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/12 09:51:45 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

static bool	is_valid_var(t_data *exec, char *var, int i)
{
	if (ft_strncmp(exec->env[i], var, ft_strlen(var)) == 0
		&& exec->env[i][ft_strlen(var)] == '=')
		return (true);
	return (false);
}

int	ft_unset(t_command_tree *tree, t_data *exec)
{
	int	i;

	i = 0;
	if (tree->argument[1] == NULL)
		return (EXIT_FAILURE);
	if (find_equal(tree->argument[1]) == true)
		return (EXIT_FAILURE);
	while (exec->env[i] != NULL)
	{
		if (is_valid_var(exec, tree->argument[1], i) == true)
		{
			while (exec->env[i + 1] != NULL)
			{
				free(exec->env[i]);
				exec->env[i] = ft_strdup(exec->env[i + 1]);
				i++;
			}
			free(exec->env[i]);
			exec->env[i] = NULL;
			exec->env_len--;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
