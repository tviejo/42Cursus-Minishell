/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 05:00:55 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/22 13:24:59 by tviejo           ###   ########.fr       */
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
		cmdline = readline("minishell> ");
		if (!cmdline)
			break ;
		add_history(cmdline);
		cmdtree = parse_cmdline(p, cmdline);
		print_cmdtree(cmdtree, p->operators, 0);
		calloc_pid(&exec, cmdtree);
		exec_cmdtree(cmdtree, &exec);
		free_cmdtree(p);
		free(cmdline);
	}
	return (free_parsing(p), 0);
}
