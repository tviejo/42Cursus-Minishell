/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 09:12:59 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/24 12:12:59 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmdtree(t_cmdtree *cmdtree, t_operator *ope, int depth)
{
	char	**args;

	if (cmdtree)
	{
		ft_printf("[depth:%d][nbcmd:%d][%s]", depth, cmdtree->nb_command,
			ope[cmdtree->type].token);
		args = cmdtree->argument;
		if (args)
			while (*args)
				ft_printf(" %s", *args++);
		ft_printf("\n");
		if (cmdtree->left)
			print_cmdtree(cmdtree->left, ope, depth + 1);
		if (cmdtree->right)
			print_cmdtree(cmdtree->right, ope, depth + 1);
	}
}

void	print_node(t_cmdtree *cmdtree, t_operator *ope)
{
	if (cmdtree->type > nt_piped_cmd)
		ft_printf("[%s]", ope[cmdtree->type].token);
	else
		ft_printf("[%s]", cmdtree->argument[0]);
}

void	if_debug_print_npi_stack(t_data *p)
{
	if (p->debug_mode > 0)
		stack_print(p->pile_npi, false,
			(t_print_elem_fct)print_node, p->operators);
}
