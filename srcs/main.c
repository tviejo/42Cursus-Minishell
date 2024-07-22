/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 05:00:55 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/22 15:20:43 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_parsing *const	p = init_parsing();
	char				*cmdline;
	t_command_tree		*cmdtree;
	t_exec				exec;

	argc = 0;
	argv = NULL;
	store_env(&exec, env);
	if (p == NULL)
		return (-1);
	rl_bind_key('\t', rl_complete);
	using_history();
	while (1)
	{
		signal(SIGINT, signal_handler);
		g_signal = 0;
		cmdline = readline("minishell> ");
		if (!cmdline)
			break ;
		add_history(cmdline);
		cmdtree = parse_cmdline(p, cmdline);
		//print_cmdtree(cmdtree, p->operators, 0);
		calloc_pid(&exec, cmdtree);
		exec.oldtype = nt_command;
		exec_cmdtree(cmdtree, &exec);
		ft_free_pid(&exec);
		wait_all_process();
		free_cmdtree(p);
		free(cmdline);
	}
	free_env(&exec);
	return (free_parsing(p), 0);
}
