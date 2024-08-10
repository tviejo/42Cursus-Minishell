/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 09:12:59 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/10 08:18:02 by ade-sarr         ###   ########.fr       */
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
	int				branch_length;

	if (p == NULL)
		return ;
	if (p->prnxpos == pct->child_xpos)
		pct->branch_xpos += (ft_dprintf(pct->fd, "\u2502"), 1);
	else if (p->prnxpos < pct->child_xpos)
	{
		branch_length = pct->child_xpos - p->prnxpos;
		if (pct->branch_xpos > p->prnxpos)
			branch_length -= pct->branch_xpos - p->prnxpos - 2;
		ft_dprintf(pct->fd, "\u2514");
		print_str_xtimes(pct->fd, "\u2500", branch_length - 2);
		ft_dprintf(pct->fd, "\u2510");
		pct->branch_xpos += branch_length;
	}
	else
	{
		ft_dprintf(pct->fd, "\u250C");
		print_str_xtimes(pct->fd, "\u2500", p->prnxpos - pct->child_xpos - 1);
		ft_dprintf(pct->fd, "\u2518");
	}
}

void	print_node(t_printcmdtree *pct, t_cmdtree *node, bool prnbranch)
{
	char			**args;

	if (prnbranch)
	{
		print_branch(pct, node);
		node->prnxpos = pct->child_xpos;
		args = node->argument;
		if (node->type > nt_piped_cmd)
			pct->child_xpos += 3 + ft_strlen(pct->ope[node->type].token);
		while (args && *args)
			pct->child_xpos += 3 + ft_strlen(*args++);
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
		pct->child_xpos = (ft_dprintf(pct->fd, "\n"), 0);
	return (count);
}

void	print_cmdtree(t_data *ms, int fd)
{
	t_printcmdtree	pct;

	ft_dprintf(fd, CORANGE);
	if (ms->cmdtree == NULL)
		ft_dprintf(fd, " [cmdtree is NULL]\n");
	else
	{
		pct = (t_printcmdtree){.targetdepth = 0, fd, ms->operators,
			.child_xpos = 1, .branch_xpos = 2, .prnbranch = true};
		ft_dprintf(fd, "  ");
		while (print_cmdtree_node(&pct, ms->cmdtree, 0))
		{
			pct.prnbranch = false;
			print_cmdtree_node(&pct, ms->cmdtree, 0);
			pct.prnbranch = true;
			pct.targetdepth++;
			pct.child_xpos = 1;
			pct.branch_xpos = 2;
			ft_dprintf(fd, "  ");
		}
		if (ms->debug_mode > 1)
			print_cmdtree_node_v1(ms->cmdtree, ms->operators, 0, fd);
	}
	ft_dprintf(fd, RESET);
}
