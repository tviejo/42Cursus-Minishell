/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:55:18 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/09 22:49:32 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0 && !((str[i] == '-' || str[i] == '+')
				&& i == 0))
			return (false);
		i++;
	}
	return (true);
}

int	ft_free_all(t_data *exec)
{
	ft_free_pid(exec);
	close_std_fd(exec);
	free_cmdtree(exec);
	free_env(exec);
	free_parsing(exec);
	ft_lstclear_process(&exec->proccess);
	return (EXIT_SUCCESS);
}

int	exit_parameter(t_data *exec, int return_value)
{
	if (exec->oldtype != nt_pipe)
		clear_terminal(exec->env);	
	ft_free_all(exec);
	exit(return_value);
}

int	ft_exit(t_command_tree *tree, t_data *exec)
{
	if (exec->oldtype != nt_pipe)
		ft_putstr_fd("exit\n", 1);
	if (tree->argument[1] != NULL)
	{
		if (ft_isnumber(tree->argument[1]) == false)
		{
			ft_dprintf(2, CRED "%sexit: %s: numeric argument required\n" RESET,
				MINI, tree->argument[1]);
			exit_parameter(exec, 2);
		}
		else if (tree->argument[2] != NULL)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (EXIT_FAILURE);
		}
		else if (ft_atoi(tree->argument[1]) > 255
			|| ft_atoi(tree->argument[1]) < 255)
			exit_parameter(exec, ft_atoi(tree->argument[1]) % 256);
		else if (ft_atoi(tree->argument[1]) < 0)
			exit_parameter(exec, 256 + ft_atoi(tree->argument[1]));
		else
			exit_parameter(exec, ft_atoi(tree->argument[1]));
	}
	exit_parameter(exec, exec->error_code);
	return (EXIT_SUCCESS);
}
