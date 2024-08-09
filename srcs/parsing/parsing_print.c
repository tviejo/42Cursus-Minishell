/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 09:12:59 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/09 23:10:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmdtree_node_v1(t_cmdtree *cmdtree, t_operator *ope, int depth,
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
		ft_dprintf(fd, "\n" );
		if (cmdtree->left)
			print_cmdtree_node_v1(cmdtree->left, ope, depth + 1, fd);
		if (cmdtree->right)
			print_cmdtree_node_v1(cmdtree->right, ope, depth + 1, fd);
	}
}

void	print_branch(t_printcmdtree *pct, t_cmdtree *node)
{
	const t_cmdtree	*p = node->parent;

	if (p == NULL)
		return ;
	print_char_xtimes(pct->fd, ' ', p->prnxpos);
	if (p->prnxpos == pct->xpos)
		ft_dprintf(pct->fd, "\u2502");
	else
	{
		ft_dprintf(pct->fd, "\u2514");
		print_str_xtimes(pct->fd, "\u2500", pct->xpos - p->prnxpos - 1);
		ft_dprintf(pct->fd, "\u2510");
	}
}

void	print_node(t_printcmdtree *pct, t_cmdtree *node, bool prnbranch)
{
	char			**args;

	if (prnbranch)
	{
		print_branch(pct, node);
		node->prnxpos = pct->xpos;
		args = node->argument;
		if (node->type > nt_piped_cmd)
			pct->xpos += 2 + ft_strlen(pct->ope[node->type].token);
		while (args && *args)
			pct->xpos += 3 + ft_strlen(*args++);
	}
	else
	{
		args = node->argument;
		if (node->type <= nt_piped_cmd)
			ft_dprintf(pct->fd, " [%s]", *args++);
		else
			ft_dprintf(pct->fd, " [%s]", pct->ope[node->type].token);
		while (args && *args)
			ft_dprintf(pct->fd, " '%s'", *args++);
	}
}

int	print_cmdtree_node(t_printcmdtree *pct, t_cmdtree *tree, int depth)
{
	int		count;

	count = 0;
	if (tree)
	{
		if (depth == pct->targetdepth)
		{
			print_node(pct, tree, pct->prnbranch);
			count++;
		}
		if (depth < pct->targetdepth)
		{
			count += print_cmdtree_node(pct, tree->left, depth + 1);
			count += print_cmdtree_node(pct, tree->right, depth + 1);
		}
	}
	if (depth == 0)
		pct->xpos = (ft_dprintf(pct->fd, "\n"), 0);
	return (count);
}

void	print_cmdtree(t_data *ms, int fd)
{
	t_printcmdtree	pct;

	if (ms->cmdtree == NULL)
		ft_dprintf(fd, " [cmdtree is NULL]\n");
	else
	{
		pct = (t_printcmdtree){.targetdepth = 0, fd, ms->operators, .xpos = 1,
			.prnbranch = true};
		while (print_cmdtree_node(&pct, ms->cmdtree, 0))
		{
			pct.prnbranch = false;
			print_cmdtree_node(&pct, ms->cmdtree, 0);
			pct.prnbranch = true;
			pct.targetdepth++;
			pct.xpos = 1;
		}
		if (ms->debug_mode > 1)
			print_cmdtree_node_v1(ms->cmdtree, ms->operators, 0, fd);
	}
}
