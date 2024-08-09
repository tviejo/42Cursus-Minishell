/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:55:01 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/09 21:33:36 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_builtin(t_command_tree *tree)
{
	if (!ft_strncmp(tree->argument[0], "echo", 5))
		return (b_echo);
	else if (!ft_strncmp(tree->argument[0], "cd", 3))
		return (b_cd);
	else if (!ft_strncmp(tree->argument[0], "env", 4))
		return (b_env);
	else if (!ft_strncmp(tree->argument[0], "pwd", 4))
		return (b_pwd);
	else if (!ft_strncmp(tree->argument[0], "unset", 6))
		return (b_unset);
	else if (!ft_strncmp(tree->argument[0], "export", 7))
		return (b_export);
	else if (!ft_strncmp(tree->argument[0], "exit", 5))
		return (b_exit);
	return (0);
}

int	exec_builtin(t_command_tree *tree, t_data *exec)
{
	int	builtin;

	exec->error_code = 0;
	builtin = find_builtin(tree);
	if (builtin == b_echo)
		return (ft_echo(tree));
	else if (builtin == b_cd)
		return (ft_cd(tree, exec));
	else if (builtin == b_env)
		return (ft_env(exec, tree));
	else if (builtin == b_pwd)
		return (ft_pwd(exec));
	else if (builtin == b_unset)
		return (ft_unset(tree, exec));
	else if (builtin == b_export)
		return (ft_export(tree, exec));
	else if (builtin == b_exit)
		return (ft_exit(tree, exec));
	return (EXIT_FAILURE);
}
/*
int	main(int argc, char **argv, char **env)
{
	t_data			exec;
	t_command_tree	tree;

	argc = 0;
	argv = NULL;
	store_env(&exec, env);
	tree.type = nt_command;
	tree.argument = malloc(sizeof(char *) * 4);
	tree.argument[0] = "exit";
	tree.argument[1] = "LD_PRELOAD";
	tree.argument[2] = NULL;
	tree.argument[3] = NULL;
	exec_builtin(&tree, &exec);
	free_env(&exec);
	free(tree.argument);
	return (EXIT_SUCCESS);
}
*/
