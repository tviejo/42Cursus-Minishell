/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 09:12:59 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/22 07:20:24 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmdtree(t_cmdtree *cmdtree, t_operator *ope, int depth)
{
	//bool	firstprint;
	char	**args;
	
	if (cmdtree)
	{
		/*if (cmdtree->type > nt_command)
			ft_printf("[depth:%d][%s]\n", depth, ope[cmdtree->type].token);
		else
			ft_printf("[depth:%d][%s]\n", depth, cmdtree->argument[0]);*/
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
		//return (true);
	}
	//return (false);
}

void	print_node(t_cmdtree *cmdtree, t_operator *ope)
{
	if (cmdtree->type >= 1)
		ft_printf("[%s]", ope[cmdtree->type].token);
	else
		ft_printf("[%s]", cmdtree->argument[0]);
}
