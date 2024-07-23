/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 05:00:55 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/23 16:34:45 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_minishell(void)
{
	printf("    __  ________   ___________ __  __________    __ \n");
	printf("   /  |/  /  _/ | / /  _/ ___// / / / ____/ /   / / \n");
	printf("  / /|_/ // //  |/ // / |__ |/ /_/ / __/ / /   / /  \n");
	printf(" / /  / // // /|  // / ___/ / __  / /___/ /___/ /___\n");
	printf("/_/  /_/___/_/ |_/___//____/_/ /_/_____/_____/_____/\n\n");
	return (0);
}
int	main(int argc, char **argv, char **env)
{
	char			*cmdline;
	t_command_tree	*cmdtree;
	t_data			exec;

	t_data *const p = init_data();
	argc = 0;
	argv = NULL;
	store_env(&exec, env);
	if (p == NULL)
		return (-1);
	rl_bind_key('\t', rl_complete);
	using_history();
	print_minishell();
	while (1)
	{
		cmdline = readline("minishell> ");
		while (cmdline != NULL && (cmdline[0] == '\0' || cmdline[0] == '\n'))
			cmdline = readline("minishell>");
		signal(SIGINT, signal_handler);
		g_signal = 0;
		add_history(cmdline);
		cmdtree = parse_cmdline(p, cmdline);
		// print_cmdtree(cmdtree, p->operators, 0);
		calloc_pid(&exec, cmdtree);
		exec.oldtype = 0;
		exec.side = e_left;
		dup_std(&exec);
		exec_cmdtree(cmdtree, &exec);
		dup2(exec.dupstdin, 0);
		dup2(exec.dupstdout, 1);
		close_std_fd(&exec);
		ft_free_pid(&exec);
		free_cmdtree(p);
		free(cmdline);
	}
	free_env(&exec);
	return (free_parsing(p), 0);
}
