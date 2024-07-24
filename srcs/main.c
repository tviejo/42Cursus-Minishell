/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 05:00:55 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/24 15:20:07 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	print_minishell(void)
{
	ft_printf("    __  ________   ___________ __  __________    __ \n");
	ft_printf("   /  |/  /  _/ | / /  _/ ___// / / / ____/ /   / / \n");
	ft_printf("  / /|_/ // //  |/ // / |__ |/ /_/ / __/ / /   / /  \n");
	ft_printf(" / /  / // // /|  // / ___/ / __  / /___/ /___/ /___\n");
	ft_printf("/_/  /_/___/_/ |_/___//____/_/ /_/_____/_____/_____/\n\n");
	return (0);
}

void	execute(t_data *exec, t_cmdtree *cmdtree)
{
	calloc_pid(exec, cmdtree);
	exec->oldtype = 0;
	exec->side = e_left;
	dup_std(exec);
	exec_cmdtree(cmdtree, exec);
	dup2(exec->dupstdin, 0);
	dup2(exec->dupstdout, 1);
	close_std_fd(exec);
	ft_free_pid(exec);
}

void	init(t_data *exec, char **env)
{
	exec->debug_mode = 0;
	exec->error_code = 0;
	if (!init_parsing(exec))
		exit (-1);
	store_env(exec, env);
	rl_bind_key('\t', rl_complete);
	using_history();
	print_minishell();
}

int	main(int argc, char **argv, char **env)
{
	char			*cmdline;
	t_command_tree	*cmdtree;
	t_data			*exec;

	(void)argc;
	(void)argv;
	exec = malloc(sizeof(t_data));
	if (exec == NULL)
		return (ft_putstr_fd("minishell: error: malloc failed\n", 2), 1);
	init(exec, env);
	while (1)
	{
		//printf("error code: %d\n", exec->error_code);
		cmdline = readline("minishell> ");
		while (cmdline != NULL && (cmdline[0] == '\0' || cmdline[0] == '\n'))
			cmdline = readline("minishell>");
		signal(SIGINT, signal_handler);
		g_signal = 0;
		add_history(cmdline);
		cmdtree = parse_cmdline(exec, cmdline);
		free(cmdline);
		if (exec->debug_mode > 0)
			print_cmdtree(cmdtree, exec->operators, 0);
		execute(exec, cmdtree);
		free_cmdtree(exec);
	}
	free_env(exec);
	return (free_parsing(exec), 0);
}
