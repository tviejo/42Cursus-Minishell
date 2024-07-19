/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:19:40 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/19 02:21:35 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*


t_cmdtree	*parse_cmdline(char *cmdline)
{
	while (*cmdline)
	{
		cmdline++;
	}
	return (NULL);
}

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
		cmdtree = parse_cmdline(cmdline);
		print_cmdtree(cmdtree);
		free(cmdline);
	}
	return (free_parsing(p), 0);
}
*/
