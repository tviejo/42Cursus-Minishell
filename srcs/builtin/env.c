/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:55:13 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/28 11:55:16 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

int ft_env(t_data *exec, t_command_tree *tree)
{
    int i;

    i = 0;
    if (tree->argument[1] != NULL)
    {
        ft_putstr_fd("env: '", 2);
        ft_putstr_fd(tree->argument[1], 2);
        ft_putstr_fd("': No such file or directory\n", 2);
        exec->error_code = 127;
        return (EXIT_FAILURE);
    }
    while (exec->env[i])
    {
        ft_putstr_fd(exec->env[i], 1);
        ft_putstr_fd("\n", 1);
        i++;
    }
    return (EXIT_SUCCESS);
}