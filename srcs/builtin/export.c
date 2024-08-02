/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:55:21 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/02 13:33:10 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_env_var(char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i])
	{
		if (env_var[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

int	len_env_var(char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	return (i);
}

char	**ft_strdup_env(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (new_env == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (new_env[i] == NULL)
		{
			ft_free_split(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	print_sorted_env(t_data *exec)
{
	int		i;
	int		j;
	char	**temp_env;

	i = 0;
	temp_env = ft_strdup_env(exec->env);
	while (temp_env[i])
	{
		j = i + 1;
		while (temp_env[j])
		{
			if (ft_strncmp(temp_env[i], temp_env[j],
					len_env_var(temp_env[i])) > 0)
				ft_swap_env(temp_env, i, j);
			j++;
		}
		ft_dprintf(1, "export %s\n", temp_env[i]);
		i++;
	}
	ft_free_split(temp_env);
	return (EXIT_SUCCESS);
}

int	ft_export(t_command_tree *tree, t_data *exec)
{
	int	i;

	if (tree->argument[1] == NULL)
	{
		print_sorted_env(exec);
		return (EXIT_SUCCESS);
	}
	if (is_env_var(tree->argument[1]) == false)
		return (EXIT_FAILURE);
	i = 0;
	while (exec->env[i])
	{
		if (ft_strncmp(exec->env[i], tree->argument[1],
				len_env_var(tree->argument[1])) == 0)
		{
			free(exec->env[i]);
			exec->env[i] = ft_strdup(tree->argument[1]);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	exec->env = expand_env(exec);
	exec->env[exec->env_len - 1] = ft_strdup(tree->argument[1]);
	return (EXIT_SUCCESS);
}
