/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 05:00:55 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/20 05:02:55 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_parsing *const	p = init_parsing();
	char				*cmdline;
	t_command_tree		*cmdtree;

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
		free_cmdtree(p);
		free(cmdline);
	}
	return (free_parsing(p), 0);
}
