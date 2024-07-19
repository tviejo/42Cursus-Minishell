/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:19:36 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/19 02:47:18 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parsing	*init_parsing(void)
{
	static t_operator	operators[] = {{"<", 2}, {"<<", 2},
	{">", 2}, {">>", 2}, {"|", 1}, {"||", 0}, {"&&", 0}, NULL};
	t_parsing *const	p = malloc(sizeof(t_parsing));

	if (p)
	{
		p->operators = operators;
		p->pile = stack_new(1024);
		if (p->pile == NULL)
			return (free_parsing(p), NULL);
	}
	return (p);
}

void	free_parsing(t_parsing *p)
{
	if (p)
	{
		stack_delete(p->pile);
		free(p);
	}
}

void	print_cmdtree(t_cmdtree *cmdtree)
{
	(void)cmdtree;
}

/*t_cmdtree	*build_tree(t_cmdtree *tree, char *cmdline)
{
	;
}*/
