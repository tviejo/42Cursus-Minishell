/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:15:39 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/07 11:41:20 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_node_priority(t_data *p, t_cmdtree *node)
{
	if (p->debug_mode >= 3)
		ft_dprintf(p->debug_fd, "[get_node_priority] node->type = %d\n",
			node->type);
	return (p->operators[node->type].priority);
}

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

void	depiler_operateurs_restants(t_data *p)
{
	t_cmdtree	*ope;

	while (gettop(p->pile_ope))
	{
		ope = pop(p->pile_ope);
		if (ope->type != nt_open_parenth)
			push(p->pile_npi, ope);
	}
}
