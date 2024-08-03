/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 09:12:59 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/03 05:55:13 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmdtree_node(t_cmdtree *cmdtree, t_operator *ope, int depth,
			int fd)
{
	char	**args;

	if (cmdtree)
	{
		ft_dprintf(fd, "[depth:%d][nbcmd:%d][sub:%d][%s]", depth,
			cmdtree->nb_command, cmdtree->subshell, ope[cmdtree->type].token);
		args = cmdtree->argument;
		if (args)
			while (*args)
				ft_dprintf(fd, " '%s'", *args++);
		ft_dprintf(fd, "\n");
		if (cmdtree->left)
			print_cmdtree_node(cmdtree->left, ope, depth + 1, fd);
		if (cmdtree->right)
			print_cmdtree_node(cmdtree->right, ope, depth + 1, fd);
	}
}

void	print_cmdtree(t_data *ms, int fd)
{
	if (ms->cmdtree == NULL)
		ft_dprintf(fd, "  [cmdtree is NULL]\n");
	else
		print_cmdtree_node(ms->cmdtree, ms->operators, 0, fd);
}

void	print_stack_node(t_cmdtree *cmdtree, t_data *ms)
{
	if (cmdtree->type > nt_piped_cmd)
		ft_dprintf(ms->debug_fd, "[%s]", ms->operators[cmdtree->type].token);
	else
		ft_dprintf(ms->debug_fd, "[%s]", cmdtree->argument[0]);
}

void	if_debug_print_npi_stack(t_data *p)
{
	if (p->debug_mode > 0)
	{
		ft_dprintf(p->pile_npi->print_fd, "  ");
		stack_print(p->pile_npi, false,
			(t_print_elem_fct)print_stack_node, p);
	}
}
