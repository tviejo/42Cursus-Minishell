/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:15:39 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/02 16:24:29 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	purger_npistack(t_stack *s)
{
	while (getsize(s) > 0)
		free_node(pop(s));
}

void	process_here_doc(t_cmdtree *node)
{
	char	*redirname;

	if (node->argument && *node->argument)
	{
		redirname = create_here_doc(*node->argument);
		free(*node->argument);
		*node->argument = redirname;
	}
}
