/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 05:00:55 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/24 12:22:28 by ade-sarr         ###   ########.fr       */
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

void	init(t_data *exec, char **env, int debug_mode)
{
	exec->debug_mode = debug_mode;
	if (!init_parsing(&exec))
		exit (-1);
	store_env(&exec, env);
	rl_bind_key('\t', rl_complete);
	using_history();
	print_minishell();
}

int	main(int argc, char **argv, char **env)
{
	char			*cmdline;
	t_command_tree	*cmdtree;
	t_data			exec;

	(void)argc;
	(void)argv;
	init(&exec, env, 1);
	while (1)
	{
		cmdline = readline("minishell> ");
		while (cmdline != NULL && (cmdline[0] == '\0' || cmdline[0] == '\n'))
			cmdline = readline("minishell>");
		signal(SIGINT, signal_handler);
		g_signal = 0;
		add_history(cmdline);
		cmdtree = parse_cmdline(p, cmdline);
		free(cmdline);
		if (exec.debug_mode > 0)
			print_cmdtree(cmdtree, p->operators, 0);
		execute(&exec, cmdtree);
		free_cmdtree(p);
	}
	free_env(&exec);
	return (free_parsing(p), 0);
}
