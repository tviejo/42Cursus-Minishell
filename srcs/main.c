/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 05:00:55 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/23 11:28:52 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char			*cmdline;
	t_command_tree	*cmdtree;
	t_exec			exec;

	t_parsing *const p = init_parsing();
	argc = 0;
	argv = NULL;
	store_env(&exec, env);
	if (p == NULL)
		return (-1);
	rl_bind_key('\t', rl_complete);
	using_history();
	while (1)
	{
		cmdline = readline("minishell> ");
		//while (cmdline == NULL && g_signal == 0)
		//	cmdline = readline("");
		signal(SIGINT, signal_handler);
		g_signal = 0;
		add_history(cmdline);
		cmdtree = parse_cmdline(p, cmdline);
		// print_cmdtree(cmdtree, p->operators, 0);
		calloc_pid(&exec, cmdtree);
		exec.oldtype = 0;
		exec.side = e_left;
		exec_cmdtree(cmdtree, &exec);
		ft_free_pid(&exec);
		free_cmdtree(p);
		free(cmdline);
		rl_redisplay();
	}
	free_env(&exec);
	return (free_parsing(p), 0);
}
